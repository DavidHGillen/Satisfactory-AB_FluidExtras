// Fill out your copyright notice in the Description page of Project Settings.


#include "ABFluidExhaust.h"
#include "Math/UnrealMathUtility.h"

void AABFluidExhaust::BeginPlay() {
	Super::BeginPlay();

	bActiveVenting = false;

	inputConnection = GetComponentByClass<UFGPipeConnectionFactory>();

	if (GetLocalRole() == ENetRole::ROLE_Authority) {
		if (mInputInventory == NULL) {
			mInputInventory = UFGInventoryLibrary::CreateInventoryComponent(this, "InputInventory");
			mInputInventory->AddArbitrarySlotSize(0, storageOverride);
		}
	}
}

//
TSubclassOf<UFGItemDescriptor> AABFluidExhaust::GetVentItem_Current() const {
	FInventoryStack stackTemp;
	if (mInputInventory->GetStackFromIndex(0, stackTemp)) {
		return stackTemp.Item.GetItemClass();
	}
	return NULL;
}

int AABFluidExhaust::GetStoredFluid_Current() const {
	FInventoryStack stackTemp;
	if (mInputInventory->GetStackFromIndex(0, stackTemp)) {
		return stackTemp.NumItems;
	}
	return 0;
}

int AABFluidExhaust::GetVentRate_Display() const {
	//if (GetLocalRole() == ENetRole::ROLE_Authority) {
	return bAutoRateVenting ? GetStoredFluid_Current() : targetRateToVent; // TODO: correct how this is done
}

//
void AABFluidExhaust::Factory_Tick(float dt) {
	// investigate to see if we should pull fluid
	if (inputConnection->IsConnected()) {
		PullFluid(dt);
	}

	// handle venting of fluid we possess
	VentFluid(dt);
}

void AABFluidExhaust::PullFluid(float dt) {
	TSubclassOf<UFGItemDescriptor> foundFluidType = inputConnection->GetFluidDescriptor();
	UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ PULL? "));

	if (foundFluidType == NULL) { return; }

	UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ PULL! "));

	int currentStore = GetStoredFluid_Current();

	// if it's a new fluid wait until we're empty to pull
	if (foundFluidType != cachedVentItem) {
		if (bActiveVenting) { return; }

		// do we like our new fluid
		if (!isValidFluid(foundFluidType)) { return; }
		ExhaustFluidUpdate(foundFluidType);
		cachedVentItem = foundFluidType;

		// clean out
		if (currentStore > 0) {
			mInputInventory->RemoveAllFromIndex(0);
			currentStore = 0;
		}
	}

	// measure pull
	int pullCount = FMath::CeilToInt(10000 * dt); // 600/min adjusted for DeltaT
	int currentSpace = storageOverride - currentStore;
	if (pullCount > currentSpace) {
		pullCount = currentSpace;
	}

	// perform pull
	if (pullCount > 0) {
		FInventoryStack tempStack;
		inputConnection->Factory_PullPipeInput(dt, tempStack, cachedVentItem, pullCount);
		if (tempStack.NumItems > 0) {
			mInputInventory->AddStackToIndex(0, tempStack);
		}
	}
}

void AABFluidExhaust::VentFluid(float dt) {
	if (mInputInventory->IsIndexEmpty(0)) {
		bActiveVenting = false;
		//UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ EMPTY"));
		return;
	}

	int currentStore = GetStoredFluid_Current();
	int ventCount = bAutoRateVenting ? currentStore : targetRateToVent;
	ventCount = FMath::CeilToInt((ventCount / 60.0f) * dt); // correct for DeltaT
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

bool AABFluidExhaust::isValidFluid(TSubclassOf<UFGItemDescriptor> item) {
	if (!bRequireSafeVent) { return true; }
	return safeItems.Contains(item);
}