// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "FGInventoryLibrary.h"
#include "FGPipeConnectionFactory.h"
#include "Buildables/FGBuildableFactory.h"
#include "Replication/FGReplicationDetailInventoryComponent.h"

#include "ABFluidExhaust.generated.h"

/**
 * 
 */
UCLASS()
class AB_FLUIDEXTRAS_API AABFluidExhaust : public AFGBuildableFactory {
	GENERATED_BODY()

public:
	// class info //

	// what should include a damage zone where it's venting, and how much damage
	UPROPERTY(EditDefaultsOnly, Category = "Exhaust System")
	TMap< TSubclassOf<UFGItemDescriptor>, float > dangerousItems;

	// limit the venting behaviour to only situations that are "safe"
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	bool bRequireSafeVent;

	// maximum storage override value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	int storageOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	TMap<EResourceForm, UNiagaraSystem*> formToParticleFX;

	// instance specific //

	// length of the space the venting will fill, suggested by the hologram, tested on every load
	UPROPERTY(BlueprintReadOnly, /*Replicated,*/ Category = "Exhaust System|Instance")
	float distance;

	// what the placed vent can safely do, suggested by the hologram, tested on every load
	UPROPERTY(BlueprintReadOnly, /*Replicated,*/ Category = "Exhaust System|Instance")
	TArray< TSubclassOf<UFGItemDescriptor> > safeItems; 

	// vent 100% of storage per minute or try to hit a specific ammount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	bool bAutoRateVenting;

	// what the specific drain rate is if we're not calculating it automatically
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust System|Instance")
	int targetRateToVent;

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

	UFUNCTION(BlueprintImplementableEvent)
	void ExhaustFluidUpdate(TSubclassOf<UFGItemDescriptor> newFluid);

protected:
	virtual void Factory_Tick(float dt) override;
	//virtual void Factory_TickProducing(float dt);
	//virtual void Factory_StopProducing();

	//void StartProductionLoopEffects(bool didStartProducing);
	//void StopProductionLoopEffects(bool didStopProducing);

	virtual void PullFluid(float dt);
	virtual void VentFluid(float dt);
	virtual bool isValidFluid(TSubclassOf<UFGItemDescriptor> item);
};
