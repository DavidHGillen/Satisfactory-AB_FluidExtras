// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"

#include "ABExhaustHologram.generated.h"

/**
 * Abstract class for BP implemntation of checks
 * BP implemntation gives better control to this and other mods
 */
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
 * May have a collection or singular saftey check to visualize, all checks will be run at construction
 * Has a build mode per saftey check which are tracked per index, -1 indicates all checks
 */
UCLASS(Category = "Exhaust System")
class AB_FLUIDEXTRAS_API AABExhaustHologram : public AFGBuildableHologram {
	GENERATED_BODY()

	AABExhaustHologram();

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
	virtual bool CanNudgeHologram() const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
	virtual void CheckValidPlacement() override;

protected:
	virtual void ConfigureActor(class AFGBuildable* inBuildable) const;
	virtual void ConfigureComponents(class AFGBuildable* inBuildable) const;

public:
	// custom:
	virtual bool PerformSafteyChecks();
};
