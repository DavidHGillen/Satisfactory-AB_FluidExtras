// Fill out your copyright notice in the Description page of Project Settings.

#include "ABFluidExhaust.h"
#include "Math/UnrealMathUtility.h"

bool AABFluidExhaust::bIsSafteyUnlocked = false;

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

void AABFluidExhaust::Factory_Tick(float dt) {
	// what fluid are we working with
	if (!bActiveVenting) {
		UpdateFluid();
	}

	// can we do anything
	if (!activeVisualizer) { return; }

	// investigate to see if we should pull fluid
	if (inputConnection->IsConnected()) {
		PullFluid(dt);
	}

	// handle venting of fluid we possess if we're allowed
	if (activeVisualizer->checkSuccess) {
		VentFluid(dt);
	}
}

void AABFluidExhaust::UpdateFluid() {
	TSubclassOf<UFGItemDescriptor> foundFluidType = inputConnection->GetFluidDescriptor();

	if (foundFluidType == cachedVentItem) { return; }

	// do we like our new fluid
	TSubclassOf<AABExhaustVisualizer> visClass = GetRelevantVisualizer(visualizers, foundFluidType);
	cachedVentItem = foundFluidType;
	ExhaustFluidUpdate(foundFluidType, visClass);

	// if we've got no relevant visualizer don't clean up
	if (visClass == NULL) { return; }

	// clean out
	int currentStore = GetStoredFluid_Current();
	if (currentStore > 0) {
		mInputInventory->RemoveAllFromIndex(0);
		currentStore = 0;
	}
}

void AABFluidExhaust::PullFluid(float dt) {
	int currentStore = GetStoredFluid_Current();

	UE_LOG(LogTemp, Warning, TEXT("~~~ Pull"));

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
		UE_LOG(LogTemp, Warning, TEXT("~~~ EMPTY"));
		return;
	}

	int currentStore = GetStoredFluid_Current();
	int ventCount = bAutoRateVenting ? currentStore : targetRateToVent;
	ventCount = FMath::CeilToInt((ventCount / 60.0f) * dt); // correct for DeltaT
	if (ventCount <= 0) {
		ventCount = 1; //TODO: consider partials accumulation
	}
	if (ventCount > currentStore) {
		ventCount = currentStore;
	}

	if (ventCount > 0) {
		bActiveVenting = true;
		mInputInventory->RemoveFromIndex(0, ventCount);
	}
	UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ VentCount: %d"), ventCount);
}

bool AABFluidExhaust::isValidFluid(TSubclassOf<UFGItemDescriptor> item) {
	return GetRelevantVisualizer(visualizers, item) != NULL;
}

// static //

/**
 * Utility function for checking visualizers against item type.
 * Importantly it reutrns the first result traversing the array backwards.
 * Use this behaviour to prioritize more specific/important visualizers
 */
TSubclassOf<AABExhaustVisualizer> AABFluidExhaust::GetRelevantVisualizer(TArray< TSubclassOf<AABExhaustVisualizer> > visualizers, TSubclassOf<UFGItemDescriptor> item) {
	for (int i = visualizers.Num() - 1; i >= 0; i--) {
		AABExhaustVisualizer* vis = Cast< AABExhaustVisualizer>(visualizers[i]->GetDefaultObject());
		if(vis != NULL && vis->RelevantItem(item)) { return visualizers[i]; }
	}
	return NULL;
}
