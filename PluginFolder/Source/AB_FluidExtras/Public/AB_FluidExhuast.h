// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "AB_FluidExhuast.generated.h"

/**
 * 
 */
UCLASS()
class AB_FLUIDEXTRAS_API AAB_FluidExhuast : public AFGBuildableFactory
{
	GENERATED_BODY()

public:
	AAB_FluidExhuast();

	UPROPERTY(EditDefaultsOnly, Category = "Exhaust System")
	TArray< TSubclassOf<class UFGItemDescriptor> > validItems;

	UPROPERTY(EditDefaultsOnly, Category = "Exhaust System")
	bool bRequireSafeVent;

protected:
	// Factory interface
	//////////////////////////////////////////////////////
	virtual void Factory_Tick(float dt) override;
};
