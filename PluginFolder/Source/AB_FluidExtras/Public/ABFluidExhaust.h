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

public:
	// class info //

	// ordered list of which visualizers for this class which are safe
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	TArray< TSubclassOf<AABExhaustVisualizer> > safeVisualizers;

	// ordered list of which visualizers for this class which are unsafe
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	TArray< TSubclassOf<AABExhaustVisualizer> > unsafeVisualizers;

	// maximum storage override value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	int storageOverride;

	// how often to recheck
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	float safteyInspectionFrequency;

protected:
	// can exhausts be set into unsafe mode
	static bool bIsSafteyUnlocked;

public:
	// can exhausts be set into unsafe mode
	UFUNCTION(BlueprintPure)
	bool GetIsSafetyUnlocked() { return AABFluidExhaust::bIsSafteyUnlocked; };
	// can exhausts be set into unsafe mode
	UFUNCTION(BlueprintCallable)
	void SetIsSafetyUnlocked(bool unlocked) { AABFluidExhaust::bIsSafteyUnlocked = unlocked; };

	// instance specific //

	// ordered list of which visualizers this object should consider, later items will be checked first
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System|Instance")
	TArray< TSubclassOf<AABExhaustVisualizer> > visualizers;

	// current visualizer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, /*Replicated,*/ Category = "Exhaust System|Instance")
	AABExhaustVisualizer* activeVisualizer;

	// vent 100% of storage per minute or try to hit a specific ammount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	bool bAutoRateVenting;

	// what the specific drain rate is if we're not calculating it automatically
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	int targetRateToVent;

	// how long to a check
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System|Instance")
	float timeToSafteyInspection;

	// has this exhaust been set into unsafe mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System|Instance")
	bool bSafteyReleased;

protected:
	// are we venting now
	bool bActiveVenting = false;

	// may not be valid at some moments so don't use it in the descriptor getter when we can't tell when it will be running
	TSubclassOf<UFGItemDescriptor> cachedVentItem;

	UPROPERTY(SaveGame)
	UFGPipeConnectionFactory* inputConnection;

	UPROPERTY(SaveGame)
	UFGInventoryComponent* mInputInventory;

public:
	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual TSubclassOf<UFGItemDescriptor> GetVentItem_Current() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual int GetVentRate_Display() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	virtual int GetStoredFluid_Current() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	UFGPipeConnectionFactory* GetInputConnection() const { return inputConnection; };

public:
	void BeginPlay();

	// handoff to the Blueprint to do actor swapping and initalization etc
	UFUNCTION(BlueprintImplementableEvent)
	void ExhaustFluidUpdate(TSubclassOf<UFGItemDescriptor> newFluid, TSubclassOf<AABExhaustVisualizer> newVisualizer);

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
