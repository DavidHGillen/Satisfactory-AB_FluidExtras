// Fill out your copyright notice in the Description page of Project Settings.

#include "ABFluidExhaust.h"
#include "Math/UnrealMathUtility.h"

void AABFluidExhaust::BeginPlay() {
	mInputInventory = NewObject<UFGInventoryComponent>(this);
	FinishAndRegisterComponent(mInputInventory);
	mInputInventory->AddArbitrarySlotSize(0, storageOverride);

	Super::BeginPlay();

	bActiveVenting = false;
	bActivePurge = false;
	cachedFoundFluid = NULL;
	inputConnection = GetComponentByClass<UFGPipeConnectionFactory>();

	nextInspection = FDateTime::Now() + FTimespan::FromSeconds(
		locationInspectionFrequency * FMath::FRandRange(0.85f, 1.15f)
	);

	UpdateVisualizerList();

	if (maxRatePerMin <= 0) { UE_LOG(LogTemp, Error, TEXT("!!!! ASSERTATION FAILED !!!!!, maxRatePerMin is too low at %d"), maxRatePerMin); }
	if (storageOverride <= 10000) { UE_LOG(LogTemp, Error, TEXT("!!!! ASSERTATION FAILED !!!!!, storageOverride is too low at %d"), storageOverride); }
}

TSubclassOf<UFGItemDescriptor> AABFluidExhaust::GetVentItem_Current() const {
	if (mInputInventory == NULL || mInputInventory->IsEmpty()) { return NULL; }

	FInventoryStack stackTemp;
	if (mInputInventory->GetStackFromIndex(0, stackTemp)) {
		return stackTemp.Item.GetItemClass();
	}

	return NULL;
}

int AABFluidExhaust::GetStoredFluid_Current() const {
	if (mInputInventory == NULL || mInputInventory->IsEmpty()) { return 0; }

	FInventoryStack stackTemp;
	if (mInputInventory->GetStackFromIndex(0, stackTemp)) {
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

	visualizers.Append(safeVisualizers);

	if (!bSafteyEngaged) {
		visualizers.Append(unsafeVisualizers);
	}

	UE_LOG(LogTemp, Warning, TEXT("~~~~ Visualizers: "));
	for (int i = 0; i < visualizers.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("~ %s"), *visualizers[i].GetDefaultObject()->FriendlyName.ToString());
	}

	// simplest way to cause a re-examination of whether the fluid can be vented
	cachedFoundFluid = NULL;
}

void AABFluidExhaust::Factory_Tick(float dt) {
	TSubclassOf<UFGItemDescriptor> foundFluidType = inputConnection->GetFluidDescriptor();
	TSubclassOf<UFGItemDescriptor> storedItem = GetVentItem_Current();
	int storedUnits = GetStoredFluid_Current();
	bActiveVenting = false;

	UE_LOG(LogTemp, Warning, TEXT("~~~~ FTick: %s"), *nextInspection.ToString());

	// if a new fluid is waiting we need to switch our visualizer, but we should only do that when empty
	if (cachedFoundFluid != foundFluidType || bActivePurge) {
		cachedFoundFluid = foundFluidType;

		UE_LOG(LogTemp, Warning, TEXT("~~~~ FluidSurprise = "));

		if (storedUnits == 0) {
			bActivePurge = false;

			UE_LOG(LogTemp, Warning, TEXT("~~~~ EmptySoSwitch:"));

			TSubclassOf<AABExhaustVisualizer> visClass = GetRelevantVisualizer(visualizers, cachedFoundFluid);
			AsyncTask(ENamedThreads::GameThread, [this, visClass](){
				UpdateToFluidBroadcast(visClass);
			});
			
			// give the system a tick to avoid race conditions given the threaded call above
			return;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("~~~~ PURGE! "));
			bActivePurge = true;
		}
	}

	// having a visualizer tells us the item is okay, but we still need to ask if it can run
	if (activeVisualizer != NULL && activeVisualizer->validLocation) {
		UE_LOG(LogTemp, Warning, TEXT("~~~~ ACTION = "));

		if (!bActivePurge && inputConnection->IsConnected()) {
			PullFluid(dt, storedUnits);
		}

		VentFluid(dt);
	}

	// check time for visualizer location
	if (FDateTime::Now() > nextInspection) {
		LocationCheckBroadcast();
		nextInspection = FDateTime::Now() + FTimespan::FromSeconds(
			locationInspectionFrequency * FMath::FRandRange(0.85f, 1.15f)
		);
	}

	// bend the display towards the actual amount and paper over some situations where the numbers might worry people
	if (bActivePurge) {
		displayVentRate = maxRatePerMin;
	} else if(!bAutoRateVenting && actualVentRate > (targetVentRate - 100)) {
		displayVentRate = targetVentRate;
	} else {
		int delta = actualVentRate - displayVentRate;
		if (delta > -10 && delta < 10) {
			displayVentRate = actualVentRate;
		} else {
			displayVentRate += delta / 2;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("~ display %d"), displayVentRate);
}

void AABFluidExhaust::PullFluid(float dt, int currentStore) {

	UE_LOG(LogTemp, Warning, TEXT("~~~~ PullFluid = "));

	// measure pull
	int pullCount = FMath::CeilToInt(10000 * dt); // 600/min adjusted for DeltaT, fine being wrong
	int currentSpace = storageOverride - currentStore;
	if (pullCount > currentSpace) {
		pullCount = currentSpace;
	}

	// perform pull
	if (pullCount > 0) {
		UE_LOG(LogTemp, Warning, TEXT("~ %d"), pullCount);
		FInventoryStack tempStack;
		inputConnection->Factory_PullPipeInput(dt, tempStack, cachedFoundFluid, pullCount);
		if (tempStack.NumItems > 0) {
			mInputInventory->AddStackToIndex(0, tempStack);
		}
	}
}

void AABFluidExhaust::VentFluid(float dt) {

	UE_LOG(LogTemp, Warning, TEXT("~~~~ VentFluid = "));

	int currentStore = GetStoredFluid_Current();
	float maxThisTick = (float(maxRatePerMin) / 60.0f) * dt; // correct for DeltaT
	float ventCount, ventRate;

	// determine how much we're venting
	if (bActivePurge) {
		ventRate = maxRatePerMin;
	} else {
		// TODO: wanted to do some kind of anti jank pulsing logic here using minimums but I need to think harder
		/*float itemsPerSec = (minRatePerMin / 60) * minRuntime;
		int minStoreToVent = 0;// FMath::CeilToInt(itemsPerSec * dt);

		if (currentStore <= minStoreToVent) {
			bActiveVenting = false;
			return;
		}*/

		ventRate = bAutoRateVenting ? currentStore : targetVentRate;
	}

	UE_LOG(LogTemp, Warning, TEXT("~ desire/m %f"), ventRate);

	// apply the venting
	ventCount = (ventRate / 60.0f) * dt; // correct for DeltaT

	UE_LOG(LogTemp, Warning, TEXT("~ deltaT   %f"), ventCount);
	if (fracationAccumulator > 1.0f) {
		fracationAccumulator -= 1.0f;
		ventCount += 1.0f;
	}
	if (ventCount > currentStore) {
		ventCount = currentStore;
	}
	if (ventCount > maxThisTick) {
		ventCount = maxThisTick;
	}

	UE_LOG(LogTemp, Warning, TEXT("~ adjust   %f"), ventCount);
	if (ventCount > 0) {
		bActiveVenting = true;

		int unitsThisTick = int(ventCount);
		fracationAccumulator += ventCount - unitsThisTick;

		mInputInventory->RemoveFromIndex(0, unitsThisTick);
	}

	UE_LOG(LogTemp, Warning, TEXT("~ final    %f"), ventCount);
	actualVentRate = FMath::CeilToInt((ventCount / dt) * 60.0f);
	UE_LOG(LogTemp, Warning, TEXT("~ actual/m %d"), actualVentRate);
}

// static //

/**
 * Utility function for checking visualizers against item class.
 * Importantly it returns the first result traversing the array backwards.
 * Use this behaviour to prioritize more specific/important visualizers.
 * Unsafe visualizers superceed safe visualizers.
 */
TSubclassOf<AABExhaustVisualizer> AABFluidExhaust::GetRelevantVisualizer(TArray< TSubclassOf<AABExhaustVisualizer> > visualizers, TSubclassOf<UFGItemDescriptor> item) {
	for (int i = visualizers.Num() - 1; i >= 0; i--) {
		AABExhaustVisualizer* vis = Cast< AABExhaustVisualizer>(visualizers[i]->GetDefaultObject());
		if(vis != NULL && vis->CheckRelevantItem(item)) { return visualizers[i]; }
	}
	return NULL;
}
