// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme
#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPipelineAttachmentHologram.h"
#include "ABJunctionHologram.generated.h"

/**
 * 
 */
UCLASS()
class AB_FLUIDEXTRAS_API AABJunctionHologram : public AFGPipelineAttachmentHologram
{
	GENERATED_BODY()

public:
	AABJunctionHologram();

	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;

protected:
	virtual void ScrollRotate(int32 delta, int32 step) override;
	virtual int32 GetRotationStep() const override;
};
