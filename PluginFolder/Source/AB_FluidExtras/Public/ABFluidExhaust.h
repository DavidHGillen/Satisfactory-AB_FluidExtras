// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "FGInventoryLibrary.h"
#include "FGPipeConnectionFactory.h"
#include "Buildables/FGBuildableFactory.h"

#include "ABExhaustVisualizer.h"

#include "ABFluidExhaust.generated.h"

/**
 * Perform the necessary pipeline attachment of the exhaust building and interaction with inventories.
 * 
 * Explictly has a safe and unsafe mode that allow venting of different items.
 * Visualizers should be made to match the BP implemntation of different versions of this class.
 * Several pieces of code are handed off to the BP expecting unique issues with each veersion.
 */
UCLASS()
class AB_FLUIDEXTRAS_API AABFluidExhaust : public AFGBuildableFactory {
	GENERATED_BODY()

public:
	// class info //

	// ordered list of which visualizers for this class which are for safe mode only
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	TArray< TSubclassOf<AABExhaustVisualizer> > safeVisualizers;

	// ordered list of which visualizers for this class which are for unsafe mode
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	TArray< TSubclassOf<AABExhaustVisualizer> > unsafeVisualizers;

	// in local space, what is the offset visualizers are expected to spawn at
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	FVector visualizerOffset;

	// maximum storage override value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	int storageOverride;

	// maximum rate value. Units/min
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	int maxRatePerMin;

	// minimum rate value. Units/min
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	int minRatePerMin;

	// minimum vent runtime in seconds
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	float minRuntime;

	// how often to recheck aproximately, randomized to adjust demand spikes
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	float locationInspectionFrequency;

	// set the bp specific saftey lock
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	void ForceSafteySystemUnlocked(bool isUnlocked = false);

	// check the bp specific saftey lock
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	bool CheckSafteySystemUnlocked();

	// instance specific //

	// ordered list of which visualizers this object should consider, later items will be checked first
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System|Instance")
	TArray< TSubclassOf<AABExhaustVisualizer> > visualizers;

	// current visualizer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	AABExhaustVisualizer* activeVisualizer;

	// vent 100% of storage per minute or try to hit a specific ammount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	bool bAutoRateVenting;

	// what the desired drain rate is in the UI if we're not calculating it automatically. Units/min
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	int targetVentRate;

	// delegate //
	// new fluid types
	UDELEGATE(BlueprintAuthorityOnly)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateToFluidDelegate,
		TSubclassOf<UFGItemDescriptor>, fluidClass,
		TSubclassOf<AABExhaustVisualizer>, visClass
	);

	UPROPERTY(BlueprintAssignable, Category = "Exhaust System")
	FUpdateToFluidDelegate OnUpdateToFluid;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System")
	virtual void UpdateToFluidBroadcast(TSubclassOf<AABExhaustVisualizer> visClass) {
		OnUpdateToFluid.Broadcast(cachedFoundFluid, visClass);
	};

	// location check time
	UDELEGATE(BlueprintAuthorityOnly)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLocationCheckDelegate);

	UPROPERTY(BlueprintAssignable, Category = "Exhaust System")
	FLocationCheckDelegate OnLocationCheck;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System")
	virtual void LocationCheckBroadcast() {
		OnLocationCheck.Broadcast();
	};

protected:

	// has this exhaust been set into unsafe mode
	UPROPERTY(BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	bool bSafteyEngaged = true;

	// practical vent rate, may be lower than target even when targeting due to insufficent fluid. Units/min
	int actualVentRate;

	// visually shown vent rate, lags a little behind actual rate to reduce jank and snapping. Units/min
	int displayVentRate;

	// are we venting now
	bool bActiveVenting = false;

	// do we have stuff stored and a different fluid in pipe to storage
	bool bActivePurge = false;

	FDateTime nextInspection;

	UPROPERTY(SaveGame)
	UFGPipeConnectionFactory* inputConnection;

	UPROPERTY(SaveGame)
	UFGInventoryComponent* mInputInventory;

	TSubclassOf<UFGItemDescriptor> cachedFoundFluid;

public:
	virtual void BeginPlay() override;
	//virtual void Tick(float dt) override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual TSubclassOf<UFGItemDescriptor> GetVentItem_Current() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual int GetStoredFluid_Current() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual TSubclassOf<UFGItemDescriptor> GetFoundFluid() const { return cachedFoundFluid; };

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	int GetVentRate_Display() const { return displayVentRate; };

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	UFGPipeConnectionFactory* GetInputConnection() const { return inputConnection; };

	// set the instance specific saftey state, returns true if changed
	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance", meta = (ReturnDisplayName = "WasChanged"))
	bool ForceSafteyState(bool isSafe);

	// check the instance specific saftey state
	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	bool CheckSafteyState();

	// update the instance specific visualizers to pick from
	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	void UpdateVisualizerList();

protected:
	virtual void Factory_Tick(float dt) override;

	//void StartProductionLoopEffects(bool didStartProducing);
	//void StopProductionLoopEffects(bool didStopProducing);

	virtual void PullFluid(float dt, int currentStore);
	virtual void VentFluid(float dt);

public:
	UFUNCTION(BlueprintCallable, Category = "Exhaust System")
	static TSubclassOf<AABExhaustVisualizer> GetRelevantVisualizer(TArray< TSubclassOf<AABExhaustVisualizer> > testVisualizers, TSubclassOf<UFGItemDescriptor> item);
};
