// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "FGInventoryLibrary.h"
#include "FGPipeConnectionFactory.h"
#include "Buildables/FGBuildableFactory.h"
#include "Replication/FGReplicationDetailInventoryComponent.h"
#include "AB_FluidExhuast.generated.h"

/**
 * 
 */
UCLASS()
class AB_FLUIDEXTRAS_API AAB_FluidExhuast : public AFGBuildableFactory
{
	GENERATED_BODY()

public:
	// what is possible to safely vent
	UPROPERTY(EditDefaultsOnly, Category = "Exhaust System")
	TArray< TSubclassOf<class UFGItemDescriptor> > validItems;

	// limit the venting behaviour to only situations that are "safe"
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	bool bRequireSafeVent;

	// how long in seconds a vent should last, used to ultra low rates into bursts of bigger rates
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	float minTimeVenting;

	// maximum storage override value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	int storageOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	TMap<EResourceForm, UNiagaraSystem*> formToParticleFX;

	// what the placed vent can safely do as informed by the hologram
	UPROPERTY(BlueprintReadOnly, SaveGame, /*Replicated,*/ Category = "Exhaust Instance")
	TArray< TSubclassOf<class UFGItemDescriptor> > safeItems; 

	// vent 100% of storage per minute or try to hit a specific ammount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust Instance")
	bool bAutoRateVenting;

	// what the specific drain rate is if we're not calculating it automatically
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, /*Replicated,*/ Category = "Exhaust Instance")
	int targetRateToVent;

	UPROPERTY(BlueprintReadWrite, Category = "Exhaust Instance")
	UNiagaraComponent* currentParticleFX;

protected:
	// are we venting now
	bool bActiveVenting = false;
	UFGPipeConnectionFactory* inputConnection;
	TSubclassOf<class UFGItemDescriptor> cachedVentItem;

	UPROPERTY(SaveGame)
	class UFGInventoryComponent* mInputInventory;

public:
	UFUNCTION(BlueprintCallable, Category = "Exhaust Instance")
	virtual TSubclassOf<class UFGItemDescriptor> GetCurrentVentItem() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust Instance")
	virtual int GetVentRateCurrent() const;

	UFUNCTION(BlueprintCallable, Category = "Exhaust Instance")
	virtual int GetStoredFluidCurrent() const;

public:
	void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void ExhaustFormUpdate(EResourceForm newForm);

protected:
	virtual void Factory_Tick(float dt) override;
	//virtual void Factory_TickProducing(float dt);
	//virtual void Factory_StopProducing();

	//void StartProductionLoopEffects(bool didStartProducing);
	//void StopProductionLoopEffects(bool didStopProducing);

	virtual void PullFluid(float dt);
	virtual void VentFluid(float dt);
	virtual bool isValidFluid(TSubclassOf<class UFGItemDescriptor> item);
};
