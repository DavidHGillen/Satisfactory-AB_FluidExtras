// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABJunctionHologram.h"
#include "FGPipeConnectionComponent.h"

AABJunctionHologram::AABJunctionHologram() {
}

bool AABJunctionHologram::TrySnapToActor(const FHitResult& hitResult) {
	bool result = Super::TrySnapToActor(hitResult);

	RotateFromSnappedElement();

	return result;
}

bool AABJunctionHologram::DoMultiStepPlacement(bool isInputFromARelease) {
	return Super::DoMultiStepPlacement(isInputFromARelease);
}

void AABJunctionHologram::ScrollRotate(int32 delta, int32 step) {
	Super::ScrollRotate(delta, step);

	RotateFromSnappedElement();
}

int32 AABJunctionHologram::GetRotationStep() const {
	return 15;
}

void AABJunctionHologram::RotateFromSnappedElement() {

	if (mSnappedConnectionComponent != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("isSnapped: "));
		UFGPipeConnectionComponentBase* myConnector = mPipeConnectionComponents[mSnapConnectionIndex];
		SetActorRotation(FRotator(180, 0, 0));
		AddActorLocalRotation(myConnector->GetRelativeRotation().GetInverse());
		AddActorWorldRotation(mSnappedConnectionComponent->GetComponentRotation());
		//AddActorLocalRotation(myConnector->GetComponentRotation());
		/*
		FRotator::

		GetScrollRotateValue() * -1;

		SetActorRotation();

		mSnappedConnectionComponent->GetComponentRotation();
		*/
	} /*else if (mSnappedPipeline != NULL) {

	}*/
}