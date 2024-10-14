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

public:
	UPROPERTY(EditDefaultsOnly)
	float recipeCheckDelay = 15.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFGBuildableFactory> vanillaPacker;

	UFUNCTION(BlueprintImplementableEvent)
	void NewRecipeFound(TSubclassOf<class UFGRecipe> recipe);

	UFUNCTION(BlueprintCallable, Category = "FactoryGame|Factory|Recipe")
	virtual void ForceRecipe(TSubclassOf<class UFGRecipe> recipe);

protected:
	// Factory interface
	virtual void Factory_Tick(float dt) override;
	virtual bool IsConfigured() const override;

	// packer
	static float nextRecipeCache;
	static TArray< TSubclassOf<class UFGRecipe> > recipeCache;

	TSubclassOf<UFGItemDescriptor> currentFluidIn;
	TSubclassOf<UFGItemDescriptor> currentSolidIn;

	virtual void FindRecipeFromInputs();
	virtual void tryUpdateRecipeCache(UWorld* world);
};
