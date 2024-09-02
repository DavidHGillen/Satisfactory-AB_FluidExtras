// Fill out your copyright notice in the Description page of Project Settings.

#include "ABExhaustHologram.h"
#include "ABFluidExhaust.h"
#include "Math/UnrealMathUtility.h"
#include "FGConstructDisqualifier.h"

#include "FGPipeSubsystem.h"
#include "Buildables/FGBuildableWall.h"
#include "Buildables/FGBuildableRamp.h"
#include "Buildables/FGBuildablePipeline.h"
#include "Buildables/FGBuildableRailroadTrack.h"

AABExhaustHologram::AABExhaustHologram() {
}

// factory game
void AABExhaustHologram::GetSupportedBuildModes_Implementation(TArray<TSubclassOf<UFGBuildGunModeDescriptor>>& out_buildmodes) const {
	Super::GetSupportedBuildModes_Implementation(out_buildmodes);

	for (int i = 0, l = visualizers.Num(); i < l; i++) {
		AABExhaustVisualizer* check = visualizers[i].GetDefaultObject();
		if (check->modeDescriptor) { out_buildmodes.AddUnique(check->modeDescriptor); }
	}
}

void AABExhaustHologram::OnBuildModeChanged(TSubclassOf<UFGHologramBuildModeDescriptor> buildMode) {
	// remove old build mode actor
	if (buildMode != mDefaultBuildMode) {

	}

	// add new build mode actors
	for (int i = 0, l = visualizers.Num(); i < l; i++) {
		AABExhaustVisualizer* check = visualizers[i].GetDefaultObject();
	}

	Super::OnBuildModeChanged(buildMode);
}

bool AABExhaustHologram::IsValidHitResult(const FHitResult& hitResult) const {
	if (Cast<AFGBuildableRailroadTrack>(hitResult.GetActor()) != NULL) {
		return false;
	}

	if (Cast<AFGBuildableWall>(hitResult.GetActor()) != NULL ||
	    Cast<AFGBuildablePipeline>(hitResult.GetActor()) != NULL
	) {
		return true;
	}

	return Super::IsValidHitResult(hitResult);
}

bool AABExhaustHologram::CanNudgeHologram() const {
	return mSnappedPipeConnection == NULL;
}

bool AABExhaustHologram::TrySnapToActor(const FHitResult& hitResult) {
	AActor* hitActor = hitResult.GetActor();
	const float snapTolerance = 200.0f;
	mSnappedPipeConnection = NULL;
	mSnappedBuilding = NULL;

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
			mSnappedBuilding = hitPipeline;
			SetActorTransform(mSnappedPipeConnection->GetComponentTransform());
			return true;
		}

		return false; // avoids running snap code when we already know
	}

	return Super::TrySnapToActor(hitResult);
}

void AABExhaustHologram::SetHologramLocationAndRotation(const FHitResult& hitResult) {
	AActor* hitActor = hitResult.GetActor();

	FVector localHitNormal = hitActor->GetTransform().Inverse().TransformVector(hitResult.ImpactNormal);
	FRotator outRotation = FRotator::ZeroRotator;
	FVector outLocation = FVector::Zero();

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
		if (FMath::Abs(hitResult.ImpactNormal.Z) <= 0.48f) {
			outLocation = hitResult.ImpactPoint;
			SnapToFoundationSide(hitFoundation, localHitNormal, EAxis::X, outLocation, outRotation);
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
	Super::CheckValidPlacement();
	UE_LOG(LogTemp, Warning, TEXT("~~~~ CheckValidPlacement"));
	//AABFluidExhaust::PerformSafteyChecks();
}

void AABExhaustHologram::ConfigureActor(AFGBuildable* inBuildable) const {
	AABFluidExhaust* exhaust = Cast<AABFluidExhaust>(inBuildable);
	Super::ConfigureActor(inBuildable);

	// distance
	// safe items
}

void AABExhaustHologram::ConfigureComponents(AFGBuildable* inBuildable) const {
	if (mSnappedPipeConnection != NULL) {
		AFGPipeSubsystem* pipeSubsys = AFGPipeSubsystem::GetPipeSubsystem(GetWorld());
		UFGPipeConnectionFactory* connection = inBuildable->GetComponentByClass<UFGPipeConnectionFactory>();
		connection->SetConnection(mSnappedPipeConnection);
		pipeSubsys->RegisterFluidIntegrant(connection);
	}

	Super::ConfigureComponents(inBuildable);
}