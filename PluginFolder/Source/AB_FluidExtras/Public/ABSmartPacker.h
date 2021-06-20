// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#pragma once

#include "CoreMinimal.h"

#include "Buildables/FGBuildableManufacturer.h"
#include "FGFactoryConnectionComponent.h"
#include "FGPipeConnectionComponent.h"
#include "FGRecipeManager.h"

#include "ABSmartPacker.generated.h"

/**
 * Automatically attempts to find a valid recipe every tick when ingredients have been consumed & it can no longer produce
 */
UCLASS()
class AB_FLUIDEXTRAS_API AABSmartPacker : public AFGBuildableManufacturer
{
	GENERATED_BODY()

	AABSmartPacker();

protected:
	// Factory interface
	//////////////////////////////////////////////////////
	virtual void Factory_Tick(float dt) override;
	virtual void Factory_ConsumeIngredients() override;
	virtual bool IsConfigured() const override;

	// Custom
	//////////////////////////////////////////////////////
	static float lastRecipeCache;
	static TArray< TSubclassOf<class UFGRecipe> > recipeCache;
	static TSubclassOf<UObject> vanillaPacker;

	static void tryUpdateRecipeCache(UWorld* world);

	bool isLookingforRecipe;
	TSubclassOf<UFGItemDescriptor> currentFluidIn;
	TSubclassOf<UFGItemDescriptor> currentSolidIn;

	virtual void FindRecipeFromInputs();
};
