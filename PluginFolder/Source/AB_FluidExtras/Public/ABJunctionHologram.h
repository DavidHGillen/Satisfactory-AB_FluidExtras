// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme
#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPipelineAttachmentHologram.h"
#include "ABJunctionHologram.generated.h"

UENUM()
enum class EPipelineJunc_HoloBehaviour : uint8
{
	PJHB_NONE,
	PJHB_SPIN,
	PJHB_DBLSPIN
};

/**
 * 
 */
UCLASS()
class AB_FLUIDEXTRAS_API AABJunctionHologram : public AFGPipelineAttachmentHologram
{
	GENERATED_BODY()

public:
	AABJunctionHologram();

	UPROPERTY(EditDefaultsOnly, Category = "Junction Hologram")
	EPipelineJunc_HoloBehaviour eCapAction;

	UPROPERTY(EditDefaultsOnly, Category = "Junction Hologram")
	EPipelineJunc_HoloBehaviour eGroundAction;

	UPROPERTY(EditDefaultsOnly, Category = "Junction Hologram")
	EPipelineJunc_HoloBehaviour eMidlineAction;

	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;

protected:
	virtual void ScrollRotate(int32 delta, int32 step) override;
	virtual int32 GetRotationStep() const override;

	void RotateFromSnappedElement();

	bool VanillaTrySnap(const FHitResult& hitResult);
};
