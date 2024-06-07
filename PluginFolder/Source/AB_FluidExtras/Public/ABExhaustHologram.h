// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"

#include "ABExhaustHologram.generated.h"

// Abstract class for BP implemntation of checks //
UCLASS(BlueprintType, Abstract, Category = "Exhaust System")
class AABExhaustSafteyCheck : public AActor {
	GENERATED_BODY()

public:
	// what items this saftey check pertains too
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	TArray< TSubclassOf<UFGItemDescriptor> > allowedItems;

	// what to show when switching modes
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	TSubclassOf<UFGBuildGunModeDescriptor> modeDescriptor;

	// what to say when this check passes
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	FText successMsg;

	// what to say when this check fails
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	FText failureMsg;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	void EnableSafteyCheck(AFGBuildableHologram* target);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	bool PerformSafteyCheck(AFGBuildableHologram* target);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	void RemoveSafteyCheck(AFGBuildableHologram* target);
};

// Actual hologram class //

/**
 * Perform the necessary saftey checks and pipeline attachment of the exhaust building
 * Has a build mode per saftey check and an all check mode (-1), tracked per index
 */
UCLASS(Category = "Exhaust System")
class AB_FLUIDEXTRAS_API AABExhaustHologram : public AFGBuildableHologram {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	TArray< TSubclassOf<AABExhaustSafteyCheck> > safteyChecks;

protected:
	// if we snapped to something, track it to connect when built
	UFGPipeConnectionComponentBase* mSnappedPipeConnection = NULL;

	// current build mode as per saftey check index, -1 being all checks.
	int buildmodeSelector = -1;

	// do a 180 rotation about what we're placed on
	bool bFlippedSnap = false;

public:
	// FactoryGame:
	virtual void GetSupportedBuildModes_Implementation(TArray<TSubclassOf<UFGBuildGunModeDescriptor>>& out_buildmodes) const override;
	virtual void OnBuildModeChanged(TSubclassOf<UFGHologramBuildModeDescriptor> buildMode) override;
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
	virtual void CheckValidPlacement() override;

protected:
	virtual USceneComponent* SetupComponent(USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName) override;
	virtual void ConfigureActor(class AFGBuildable* inBuildable) const;
	virtual void ConfigureComponents(class AFGBuildable* inBuildable) const;

public:
	// custom:
	virtual bool PerformSafteyChecks();
};
