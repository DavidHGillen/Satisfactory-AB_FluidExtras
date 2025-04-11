// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"

#include "ABExhaustVisualizer.h"

#include "ABExhaustHologram.generated.h"

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
	// what are the relevant visualizers for the exhaust
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	TArray< TSubclassOf<AABExhaustVisualizer> > visualizers;

	// is this a small enough wall based attachment instead of a free standing building
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System")
	bool bWallAttachment = false;

protected:
	// if we snapped to something, track it to connect when built
	UFGPipeConnectionComponentBase* mSnappedPipeConnection = NULL;

	// current visualizer mode as per index, -1 being no specific visualizer
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
};
