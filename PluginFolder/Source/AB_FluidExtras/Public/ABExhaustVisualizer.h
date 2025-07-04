// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ABExhaustVisualizer.generated.h"

class AABExhaustHologram; //fwd dec

/**
 *
 */
USTRUCT(BlueprintType, Category = "Exhaust System")
struct FABExhaustPlayerFX: public FTableRowBase {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System")
	TSubclassOf<UFGItemDescriptor> itemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System")
	float damageTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System")
	float tickRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System")
	TSoftObjectPtr<UObject> playerFX;
};

/**
 * Abstract class for BP implementation of checks
 * BP implemntation gives better control to this and other mods
 */
UCLASS(BlueprintType, Abstract, Category = "Exhaust System")
class AABExhaustVisualizer: public AActor {
	GENERATED_BODY()

public:

	// a verbal explanation of the check result
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System|Instance")
	FString checkSuccessString;

	// whether the check passed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaust System|Instance")
	bool checkSuccess = false;

	// a verbal explanation of the check result
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	FText FriendlyName;

	// what to show when switching hologram modes to this
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exhaust System")
	TSubclassOf<UFGBuildGunModeDescriptor> modeDescriptor;

	// items to filter out of responses like impacts, expanded from base classes
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Exhaust System", meta=( AllowAbstract = true ))
	TArray<TSubclassOf<AActor>> filterClasses;

	// functions

	// does this item belong to this visualizer
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	bool RelevantItem(TSubclassOf<UFGItemDescriptor> item);

	// investigate the given position to see if it is valid
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	bool PerformSafteyCheck(FTransform testStart);

	// provide an update to the visuals if needed
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	void UpdateVisuals(TSubclassOf<UFGItemDescriptor> item, float currentRate);

	// add any lines or other stuff the hologram needs for visualization
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	void ConfigureHologram(AABExhaustHologram* target);

	// what icons we should display to help people understand what we vent
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Exhaust System")
	TArray<UTexture2D*> GetHelperIcons();

	// utility
	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	void AppendTextToSuccessStatus(FText newText) {
		checkSuccessString.Append(" ");
		checkSuccessString.Append(newText.ToString());
		checkSuccessString.Append(" ");
	};

	UFUNCTION(BlueprintCallable, Category = "Exhaust System|Instance")
	void AppendStringToSuccessStatus(FString newText) {
		checkSuccessString.Append(" ");
		checkSuccessString.Append(newText);
		checkSuccessString.Append(" ");
	};
};