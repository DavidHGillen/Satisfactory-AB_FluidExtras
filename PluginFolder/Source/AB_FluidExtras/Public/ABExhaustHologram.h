// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"

#include "ABExhaustVisualizer.h"

#include "ABExhaustHologram.generated.h"

/**
 * Handle showing possible saftey checks via build mode, and placement rules for complex situations.
 * 
 * Has a wall snapping mode designed to be like pipeline wall holes and allow easy venting outside.
 * Cycling the build mode should cycle the visualizers available for the user.
 * Remember the hologram has to handle the pipe connection if snapping to existing pipes.
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
