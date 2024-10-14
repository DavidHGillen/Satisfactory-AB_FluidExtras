// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABSmartPacker.h"

// init
float AABSmartPacker::nextRecipeCache = -1.0f;
TArray< TSubclassOf<class UFGRecipe> > AABSmartPacker::recipeCache;

AABSmartPacker::AABSmartPacker() {
	currentFluidIn = nullptr;
	currentSolidIn = nullptr;
}

// Factory interface
void AABSmartPacker::Factory_Tick(float dt) {
	if (GetLocalRole() == ENetRole::ROLE_Authority) {
		//UE_LOG(LogTemp, Warning, TEXT("[ ] Its my job"));
		if (!CanProduce()) {
			//UE_LOG(LogTemp, Warning, TEXT("[ ] Can't Produce"));
			FindRecipeFromInputs();
		}
	}/* else {
		UE_LOG(LogTemp, Warning, TEXT("[ ] Not my job"));
	}*/

	Super::Factory_Tick(dt);
}

bool AABSmartPacker::IsConfigured() const {
	// we auto configure ourselves so of course we're fine
	return true;
}

// Custom
void AABSmartPacker::tryUpdateRecipeCache(UWorld* world) {
	// time limit function
	float now = world->GetRealTimeSeconds();
	if (now < nextRecipeCache) { return; }
	nextRecipeCache = now + 15.0f;

	// set recipes on cache
	AFGRecipeManager::Get(world)->GetAvailableRecipesForProducer(vanillaPacker, recipeCache);

	//UE_LOG(LogTemp, Warning, TEXT("[ ] Updating smart packer recipe cache [ %d ] Recipes found"), recipeCache.Num());
}

void AABSmartPacker::FindRecipeFromInputs() {
	TSubclassOf<UFGItemDescriptor> beltIncoming = nullptr;

	// fluid
	if (mPipeInputConnections.Num() > 0) {
		currentFluidIn = mPipeInputConnections[0]->GetFluidDescriptor();
	} else {
		currentFluidIn = nullptr;
	}
	
	// solid
	if (mFactoryInputConnections.Num() > 0) {
		TArray< FInventoryItem > peekResult;
		mFactoryInputConnections[0]->Factory_PeekOutput(peekResult, nullptr);

		for (int i = 0, l = peekResult.Num(); i < l && beltIncoming == nullptr; i++) {
			beltIncoming = peekResult[0].GetItemClass();
		}

		currentSolidIn = beltIncoming;
	} else {
		currentSolidIn = nullptr;
	}

	//UE_LOG(LogTemp, Warning, TEXT("[ ] Inputs: %s - %s"), *UFGItemDescriptor::GetItemName(currentFluidIn).ToString(), *UFGItemDescriptor::GetItemName(currentSolidIn).ToString());

	// recipe
	tryUpdateRecipeCache(GetWorld());
	TSubclassOf<class UFGRecipe> foundRecipe = nullptr;

	for (int i = 0, l = recipeCache.Num(); i < l; i++) {
		if (!recipeCache.IsValidIndex(i) || recipeCache[i] == NULL) { recipeCache.Empty();  return; }

		TArray<FItemAmount> ingredients = UFGRecipe::GetIngredients(recipeCache[i]);

		if (ingredients.Num() == 2) {
			if ((ingredients[0].ItemClass == currentFluidIn || ingredients[0].ItemClass == currentSolidIn) &&
				(ingredients[1].ItemClass == currentFluidIn || ingredients[1].ItemClass == currentSolidIn)) {
				foundRecipe = recipeCache[i];
				break;
			}
		} else if (ingredients.Num() == 1) {
			if (ingredients[0].ItemClass == currentSolidIn || ingredients[0].ItemClass == currentFluidIn) {
				foundRecipe = recipeCache[i];
				break;
			}
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("[ ] Found!: %s "), *UFGRecipe::GetRecipeName(foundRecipe).ToString());

	// set it
	if (foundRecipe != nullptr && foundRecipe != mCurrentRecipe) {
		NewRecipeFound(foundRecipe);
	}
}

// CANNOT BE CALLED FROM TICK DUE TO THREADING ISSUES HENCE BP BYPASS
void AABSmartPacker::ForceRecipe(TSubclassOf<class UFGRecipe> recipe) {
	// with packing we're deleting input inventory here, not sure that's an issue
	// with unpacking we delete jammed output, not sure that's an issue 
	ClearOutputInventoryItems();
	ClearInputInventoryItems();

	SetRecipe(recipe);

	//UE_LOG(LogTemp, Warning, TEXT("[ ] Applied!: %s "), *UFGRecipe::GetRecipeName(recipe).ToString());
}

