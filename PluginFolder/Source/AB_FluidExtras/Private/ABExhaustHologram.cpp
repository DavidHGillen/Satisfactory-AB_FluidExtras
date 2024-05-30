// Fill out your copyright notice in the Description page of Project Settings.

#include "ABExhaustHologram.h"
#include "ABFluidExhaust.h"

#include "Math/UnrealMathUtility.h"
#include "Buildables/FGBuildableWall.h"
#include "FGConstructDisqualifier.h"

// factory game
bool AABExhaustHologram::IsValidHitResult(const FHitResult& hitResult) const {
	return Super::IsValidHitResult(hitResult);
}

void AABExhaustHologram::GetSupportedBuildModes_Implementation(TArray<TSubclassOf<UFGBuildGunModeDescriptor>>& out_buildmodes) const {
	Super::GetSupportedBuildModes_Implementation(out_buildmodes);

	for (int i = 0, l = safteyChecks.Num(); i < l; i++) {
		AABExhaustSafteyCheck* check = safteyChecks[i].GetDefaultObject();
		if (check->modeDescriptor) { out_buildmodes.AddUnique(check->modeDescriptor); }
	}
}

void AABExhaustHologram::OnBuildModeChanged(TSubclassOf<UFGHologramBuildModeDescriptor> buildMode) {
	// remove old build mode actor
	if (buildMode != mDefaultBuildMode) {

	}

	// add new build mode actors
	for (int i = 0, l = safteyChecks.Num(); i < l; i++) {
		AABExhaustSafteyCheck* check = safteyChecks[i].GetDefaultObject();
	}

	Super::OnBuildModeChanged(buildMode);
}

void AABExhaustHologram::SetHologramLocationAndRotation(const FHitResult& hitResult) {
	AActor* hitActor = hitResult.GetActor();

	AFGBuildableWall* hitWall = Cast<AFGBuildableWall>(hitActor);
	if (hitWall != NULL) {
		Super::SetHologramLocationAndRotation(hitResult);
		return;
	}

	Super::SetHologramLocationAndRotation(hitResult);
	AddActorWorldOffset(FVector(0.0f, 0.0f, 175.0f));
}

USceneComponent* AABExhaustHologram::SetupComponent(USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName) {
	return Super::SetupComponent(attachParent, componentTemplate, componentName, attachSocketName);
}

void AABExhaustHologram::ConfigureActor(AFGBuildable* inBuildable) const {
	Super::ConfigureActor(inBuildable);
}

void AABExhaustHologram::ConfigureComponents(AFGBuildable* inBuildable) const {
	Super::ConfigureComponents(inBuildable);
}

// custom:
bool AABExhaustHologram::PerformSafteyChecks() {
	for (int i = 0, l = safteyChecks.Num(); i < l; i++) {
		//FAB_ExhaustSafteyCheck check = safteyChecks[i];
		//check.safteyCheckActor->PerformSafteyCheck();
	}
	return true;
}