// Fill out your copyright notice in the Description page of Project Settings.

#include "ABExhaustHologram.h"
#include "ABFluidExhaust.h"
#include "Math/UnrealMathUtility.h"
#include "FGConstructDisqualifier.h"

#include "Buildables/FGBuildableWall.h"
#include "Buildables/FGBuildableRamp.h"
#include "Buildables/FGBuildablePipeline.h"
#include "Buildables/FGBuildableRailroadTrack.h"

// factory game
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

bool AABExhaustHologram::IsValidHitResult(const FHitResult& hitResult) const {
	if (Cast<AFGBuildableRailroadTrack>(hitResult.GetActor()) != NULL) {
		return false;
	}

	if (Cast<AFGBuildableWall>(hitResult.GetActor()) != NULL) {
		return true;
	}

	if (Cast<AFGBuildablePipeline>(hitResult.GetActor()) != NULL) {
		return true;
	}

	return Super::IsValidHitResult(hitResult);
}

bool AABExhaustHologram::TrySnapToActor(const FHitResult& hitResult) {
	AActor* hitActor = hitResult.GetActor();
	const float snapTolerance = 200.0f;

	// pipeline end snapping
	AFGBuildablePipeline* hitPipeline = Cast<AFGBuildablePipeline>(hitActor);
	if (hitPipeline != NULL) {
		FTransform snapTransform;
		USplineComponent* splineRef = hitPipeline->GetSplineComponent();
		float length = splineRef->GetSplineLength();
		float distance0 = splineRef->FindDistanceClosestToWorldLocation(hitResult.Location);
		float distance1 = length - distance0;

		if (distance0 < distance1 && distance0 < snapTolerance) {
			mSnappedPipeConnection = hitPipeline->GetConnection0();
		}
		if (distance1 < distance0 && distance1 < snapTolerance) {
			mSnappedPipeConnection = hitPipeline->GetConnection1();
		}

		if (mSnappedPipeConnection != NULL) {
			SetActorTransform(mSnappedPipeConnection->GetComponentTransform());
			return true;
		}

		mSnappedPipeConnection = NULL;
		return false; // avoids running snap code when we already know
	}

	mSnappedPipeConnection = NULL;
	return Super::TrySnapToActor(hitResult);
}

void AABExhaustHologram::SetHologramLocationAndRotation(const FHitResult& hitResult) {
	FRotator outRotation = FRotator::ZeroRotator;
	FVector outLocation = FVector::Zero();
	AActor* hitActor = hitResult.GetActor();

	UE_LOG(LogTemp, Warning, TEXT("~~~~ ~~~~ ~~~~"));

	// wall placement
	AFGBuildableWall* hitWall = Cast<AFGBuildableWall>(hitActor);
	if (hitWall != NULL) {
		SnapToWall(hitWall, hitResult.ImpactNormal, hitResult.ImpactPoint, EAxis::X, FVector::Zero(), 0.0f, outLocation, outRotation);
		SetActorLocationAndRotation(outLocation, outRotation);
		if (hitWall->mAngularDepth <= 1.0f) {
			AddActorWorldOffset(FVector(0.0f, 0.0f, -25.0f));
		}
		if ((GetScrollRotateValue() / 10) % 2) {
			AddActorLocalRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
		return;
	}

	// foundations enable side snapping and handle underside snapping
	AFGBuildableFoundation* hitFoundation = Cast<AFGBuildableFoundation>(hitActor);
	if (hitFoundation != NULL) {

		// foundation side
		if (FMath::Abs(hitResult.ImpactNormal.GetAbs().Z) <= 0.48f) {
			outLocation = hitResult.ImpactPoint;
			SnapToFoundationSide(hitFoundation, hitResult.ImpactNormal, EAxis::X, outLocation, outRotation);
			SetActorLocationAndRotation(outLocation, outRotation);
			AddActorWorldOffset(FVector(0.0f, 0.0f, -25.0f));
			return;
		}

		// foundation top & bottom
		Super::SetHologramLocationAndRotation(hitResult);
		if (hitResult.ImpactNormal.Z > 0.0f) {
			AddActorWorldOffset(FVector(0.0f, 0.0f, 175.0f));
		} else {
			AddActorWorldOffset(FVector(0.0f, 0.0f, -(175.0f + hitFoundation->mHeight)));
		}
		return;
	}

	Super::SetHologramLocationAndRotation(hitResult);
	AddActorWorldOffset(FVector(0.0f, 0.0f, 175.0f));
}

void AABExhaustHologram::CheckValidPlacement() {
	mCanBePlacedInBlueprintDesigner = false; // TODO: this is gross and agressive, figure out better solution

	Super::CheckValidPlacement();
	UE_LOG(LogTemp, Warning, TEXT("~~~~ CheckValidPlacement"));
	PerformSafteyChecks();
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