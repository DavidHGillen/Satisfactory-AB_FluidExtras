// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_FluidExhuast.h"
#include "Math/UnrealMathUtility.h"

void AAB_FluidExhuast::BeginPlay() {
	Super::BeginPlay();

	inputConnection = GetComponentByClass<UFGPipeConnectionFactory>();

	if (GetLocalRole() == ENetRole::ROLE_Authority) {
		if (mInputInventory == NULL) {
			mInputInventory = UFGInventoryLibrary::CreateInventoryComponent(this, "InputInventory");
			mInputInventory->AddArbitrarySlotSize(0, storageOverride);
		}
	}
}

//
TSubclassOf<class UFGItemDescriptor> AAB_FluidExhuast::GetCurrentVentItem() const {
	FInventoryStack stackTemp;
	if (mInputInventory->GetStackFromIndex(0, stackTemp)) {
		return stackTemp.Item.GetItemClass();
	}
	return NULL;
}

int AAB_FluidExhuast::GetStoredFluidCurrent() const {
	FInventoryStack stackTemp;
	if (mInputInventory->GetStackFromIndex(0, stackTemp)) {
		return stackTemp.NumItems;
	}
	return 0;
}

int AAB_FluidExhuast::GetVentRateCurrent() const {
	return bAutoRateVenting ? GetStoredFluidCurrent() : targetRateToVent;
}

//
void AAB_FluidExhuast::Factory_Tick(float dt) {
	// investigate to see if we should pull fluid
	if (inputConnection->IsConnected()) {
		PullFluid(dt);
	}

	// handle venting of fluid we possess
	VentFluid(dt);
}

void AAB_FluidExhuast::PullFluid(float dt) {
	TSubclassOf<UFGItemDescriptor> foundFluidType = inputConnection->GetFluidDescriptor();

	if (foundFluidType == NULL) { return; }

	// if it's a new fluid wait until we're empty to pull
	if (foundFluidType != cachedVentItem) {
		if (bActiveVenting) { return; }

		// do we like our new fluid
		if (!isValidFluid(foundFluidType)) { return; }
		EResourceForm newForm = UFGItemDescriptor::GetForm(foundFluidType);
		if (cachedVentItem == NULL || UFGItemDescriptor::GetForm(cachedVentItem) != newForm) {
			ExhaustFormUpdate(newForm);
		}
		cachedVentItem = foundFluidType;

		// clean out
		if (GetStoredFluidCurrent() > 0) {
			mInputInventory->RemoveAllFromIndex(0);
		}
		//UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ TurboSuck Now: %s"), *UFGItemDescriptor::GetItemName(cachedVentItem).ToString());
	}

	// measure pull
	int pullCount = FMath::CeilToInt(10000 * dt); // 600/min
	int currentSpace = storageOverride - GetStoredFluidCurrent();
	if (pullCount > currentSpace) {
		pullCount = currentSpace;
		//UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ MaxSpace: %d"), currentSpace);
	}

	// perform pull
	if (pullCount > 0) {
		FInventoryStack tempStack;
		inputConnection->Factory_PullPipeInput(dt, tempStack, cachedVentItem, pullCount);
		if (tempStack.NumItems > 0) {
			mInputInventory->AddStackToIndex(0, tempStack);
		}
		//UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ PipePull: %d"), pullCount);
	}
}

void AAB_FluidExhuast::VentFluid(float dt) {
	if (mInputInventory->IsIndexEmpty(0)) {
		bActiveVenting = false;
		//UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ EMPTY"));
		return;
	}
	
	int ventCount = FMath::CeilToInt((GetVentRateCurrent() / 60.0f) * dt);
	int currentStore = GetStoredFluidCurrent();
	if (ventCount <= 0) {
		ventCount = 1;
	}
	if (ventCount > currentStore) {
		ventCount = currentStore;
	}

	if (ventCount > 0) {
		bActiveVenting = true;
		mInputInventory->RemoveFromIndex(0, ventCount);
	}
	//UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ VentCount: %d"), ventCount);
}

bool AAB_FluidExhuast::isValidFluid(TSubclassOf<class UFGItemDescriptor> item) {
	if (!bRequireSafeVent) { return true; }
	return safeItems.Contains(item);
}