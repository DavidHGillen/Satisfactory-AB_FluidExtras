// Fill out your copyright notice in the Description page of Project Settings.

#include "ABFluidExhaust.h"
#include "Math/UnrealMathUtility.h"

/*AABFluidExhaust::AABFluidExhaust() {
	Super();

	mInputInventory = NewObject<UFGInventoryComponent>(this);
	FinishAndRegisterComponent(mInputInventory);
}*/

void AABFluidExhaust::BeginPlay() {
	Super::BeginPlay();

	bActiveVenting = false;
	inputConnection = GetComponentByClass<UFGPipeConnectionFactory>();

	UpdateVisualizerList();
}

TSubclassOf<UFGItemDescriptor> AABFluidExhaust::GetVentItem_Current() const {
	TSubclassOf<UFGItemDescriptor> item = NULL;

	if (activeVisualizer) {
		if (cachedVentItem == NULL) {
			FInventoryStack stackTemp;
			mInputInventory->GetStackFromIndex(0, stackTemp);
			item = stackTemp.Item.GetItemClass();
		} else {
			item = cachedVentItem;
		}
	}

	return item;
}

TSubclassOf<UFGItemDescriptor> AABFluidExhaust::GetFoundFluid() const {
	return foundFluidType;
}

int AABFluidExhaust::GetStoredFluid_Current() const {
	FInventoryStack stackTemp;
	if (cachedVentItem != NULL && mInputInventory->GetStackFromIndex(0, stackTemp)) {
		return stackTemp.NumItems;
	}
	return 0;
}

bool AABFluidExhaust::ForceSafteyState(bool isSafe) {
	if (bSafteyEngaged == isSafe) { return false; }

	bSafteyEngaged = isSafe;
	UpdateVisualizerList();

	return true;
}

bool AABFluidExhaust::CheckSafteyState() {
	return bSafteyEngaged;
}

void AABFluidExhaust::UpdateVisualizerList() {
	visualizers.Empty();

	if (!bSafteyEngaged) {
		visualizers.Append(unsafeVisualizers);
	}

	visualizers.Append(safeVisualizers);

	cachedVentItem = NULL; // cause it to rethink the appropriate vizualizer
}

int AABFluidExhaust::GetVentRate_Display() const {
	//if (GetLocalRole() == ENetRole::ROLE_Authority) {
	int rate = 0;
	if (bActiveVenting) {
		rate = bAutoRateVenting ? GetStoredFluid_Current() : targetRateToVent; // TODO: correct how this is done
	}
	return rate;
}

void AABFluidExhaust::Factory_Tick(float dt) {
	// what fluid are we working with
	if (!bActiveVenting) {
		UpdateFluid();
	}

	// can we do anything we may of ingested fluids while unsafe and been reset to safe so validity check needed to respond
	if (!activeVisualizer || !activeVisualizer->checkSuccess || !isValidFluid(cachedVentItem)) {
		bActiveVenting = false;
		return;
	}

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
	foundFluidType = inputConnection->GetFluidDescriptor();

	if (foundFluidType == cachedVentItem) { return; }

	// do we like our new fluid
	TSubclassOf<AABExhaustVisualizer> visClass = GetRelevantVisualizer(visualizers, foundFluidType);
	cachedVentItem = foundFluidType;
	AsyncTask(ENamedThreads::GameThread, [this, visClass](){
		ExhaustFluidUpdate(foundFluidType, visClass);
	});

	// if we've got no relevant visualizer don't clean up
	if (visClass == NULL) { return; }

	// clean out
	if (GetStoredFluid_Current() > 0) {
		mInputInventory->RemoveAllFromIndex(0);
	}
}

void AABFluidExhaust::PullFluid(float dt) {
	int currentStore = GetStoredFluid_Current();

	//UE_LOG(LogTemp, Warning, TEXT("~~~ Pull"));

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
		//UE_LOG(LogTemp, Warning, TEXT("~~~ EMPTY"));
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
	//UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ VentCount: %d"), ventCount);
}

bool AABFluidExhaust::isValidFluid(TSubclassOf<UFGItemDescriptor> item) {
	return GetRelevantVisualizer(visualizers, item) != NULL;
}

// static //

/**
 * Utility function for checking visualizers against item type.
 * Importantly it returns the first result traversing the array backwards.
 * Use this behaviour to prioritize more specific/important visualizers
 */
TSubclassOf<AABExhaustVisualizer> AABFluidExhaust::GetRelevantVisualizer(TArray< TSubclassOf<AABExhaustVisualizer> > visualizers, TSubclassOf<UFGItemDescriptor> item) {
	for (int i = visualizers.Num() - 1; i >= 0; i--) {
		AABExhaustVisualizer* vis = Cast< AABExhaustVisualizer>(visualizers[i]->GetDefaultObject());
		if(vis != NULL && vis->RelevantItem(item)) { return visualizers[i]; }
	}
	return NULL;
}
