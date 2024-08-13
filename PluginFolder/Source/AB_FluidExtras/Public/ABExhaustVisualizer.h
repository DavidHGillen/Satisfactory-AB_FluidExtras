// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ABExhaustVisualizer.generated.h"

class AABExhaustHologram; //fwd dec
class AABFluidExhaust; //fwd dec

/**
 * Abstract class for BP implementation of checks
 * BP implemntation gives better control to this and other mods
 */
UCLASS(BlueprintType, Abstract, Category = "Exhaust System")
class AABExhaustVisualizer : public AActor {
	GENERATED_BODY()

public:
	// the specific exhaust we're visualizing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System")
	AABFluidExhaust* ownedExhaust;

	// a verbal explanation of the check result
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System")
	FString checkStatus;

	// what to show when switching hologram modes to this
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	TSubclassOf<UFGBuildGunModeDescriptor> modeDescriptor;

	// dose this item belong to this visualizer
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	bool RelevantItem(TSubclassOf<UFGItemDescriptor> item);

	// investigate the given position to see if it is valid
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	bool PerformSafteyCheck(FTransform testStart);

	// add any lines or other stuff the hologram needs for visualization
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	void ConfigureHologram(AABExhaustHologram* target);
};