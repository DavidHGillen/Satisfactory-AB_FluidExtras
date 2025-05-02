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
 * 
 */
UCLASS()
class AB_FLUIDEXTRAS_API AABFluidExhaust : public AFGBuildableFactory {
	GENERATED_BODY()

	//AABFluidExhaust();

public:
	// class info //

	// ordered list of which visualizers for this class which are for safe mode only
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	TArray< TSubclassOf<AABExhaustVisualizer> > safeVisualizers;

	// ordered list of which visualizers for this class which are for unsafe mode
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	TArray< TSubclassOf<AABExhaustVisualizer> > unsafeVisualizers;

	// maximum storage override value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	int storageOverride;

	// how often to recheck
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	float safteyInspectionFrequency;

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

	// what the specific drain rate is if we're not calculating it automatically
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	int targetRateToVent;

	// how long to a check
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	float timeToSafteyInspection;

	// delegate //
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateToFluidDelegate);

	UPROPERTY(BlueprintAssignable, Category = "Exhaust System")
	FUpdateToFluidDelegate OnUpdateToFluid;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System")
	virtual void UpdateToFluidBroadcast() { OnUpdateToFluid.Broadcast(); };

protected:

	// has this exhaust been set into unsafe mode
	UPROPERTY(BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	bool bSafteyEngaged = true;

	// are we venting now
	bool bActiveVenting = false;

	// may not be valid at some moments so don't use it in the descriptor getter when we can't tell when it will be running
	TSubclassOf<UFGItemDescriptor> cachedVentItem;

	UPROPERTY(SaveGame)
	UFGPipeConnectionFactory* inputConnection;

	UPROPERTY(SaveGame)
	UFGInventoryComponent* mInputInventory;

	TSubclassOf<UFGItemDescriptor> foundFluidType;

public:
	void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual TSubclassOf<UFGItemDescriptor> GetVentItem_Current() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual TSubclassOf<UFGItemDescriptor> GetFoundFluid() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual int GetVentRate_Display() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual int GetStoredFluid_Current() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	UFGPipeConnectionFactory* GetInputConnection() const { return inputConnection; };

	// must handoff to the Blueprint to do actor swapping and initalization etc (call in gameplay thread)
	UFUNCTION(BlueprintImplementableEvent, Category = "Exhaust System|Instance")
	void ExhaustFluidUpdate(TSubclassOf<UFGItemDescriptor> newFluid, TSubclassOf<AABExhaustVisualizer> newVisualizer);

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
	//virtual void Factory_TickProducing(float dt);
	//virtual void Factory_StopProducing();

	//void StartProductionLoopEffects(bool didStartProducing);
	//void StopProductionLoopEffects(bool didStopProducing);

	virtual void UpdateFluid();
	virtual void PullFluid(float dt);
	virtual void VentFluid(float dt);
	virtual bool isValidFluid(TSubclassOf<UFGItemDescriptor> item);

public:
	UFUNCTION(BlueprintCallable, Category = "Exhaust System")
	static TSubclassOf<AABExhaustVisualizer> GetRelevantVisualizer(TArray< TSubclassOf<AABExhaustVisualizer> > testVisualizers, TSubclassOf<UFGItemDescriptor> item);
};
