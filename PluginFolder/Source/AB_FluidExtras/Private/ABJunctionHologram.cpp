// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABJunctionHologram.h"

AABJunctionHologram::AABJunctionHologram() {
}

bool AABJunctionHologram::DoMultiStepPlacement(bool isInputFromARelease) {
	return Super::DoMultiStepPlacement(isInputFromARelease);
}

void AABJunctionHologram::ScrollRotate(int32 delta, int32 step) {
	Super::ScrollRotate(delta, step);
}

int32 AABJunctionHologram::GetRotationStep() const {
	return Super::GetRotationStep();
}