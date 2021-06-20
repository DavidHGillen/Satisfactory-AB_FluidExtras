// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABSmartPacker.h"
float AABSmartPacker::lastRecipeCache = 0.0f;
TArray< TSubclassOf<class UFGRecipe> > AABSmartPacker::recipeCache;
TSubclassOf<UObject> AABSmartPacker::vanillaPacker = nullptr;

AABSmartPacker::AABSmartPacker() {
	if (vanillaPacker == nullptr) {
		vanillaPacker = ConstructorHelpers::FClassFinder<UObject>(TEXT("/Game/FactoryGame/Buildable/Factory/Packager/Build_Packager.Build_Packager_C")).Class;
	}

	isLookingforRecipe = true;
	currentFluidIn = nullptr;
	currentSolidIn = nullptr;
}

// Factory interface
//////////////////////////////////////////////////////
void AABSmartPacker::Factory_Tick(float dt) {
	if (isLookingforRecipe) {
		FindRecipeFromInputs();
	}

	Super::Factory_Tick(dt);
}

void AABSmartPacker::Factory_ConsumeIngredients() {
	Super::Factory_ConsumeIngredients();

	// if we can't keep going, go shopping
	isLookingforRecipe = !HasRequiredIngredients();
}

bool AABSmartPacker::IsConfigured() const {
	// we auto configure ourselves so of course we're fine
	return true;
}

// Custom
//////////////////////////////////////////////////////
void AABSmartPacker::tryUpdateRecipeCache(UWorld* world) {
	// time limit function
	float now = world->GetRealTimeSeconds();
	//if (now < lastRecipeCache + 15.0f) { return; }
	lastRecipeCache = now;

	// set recipes on cache
	AFGRecipeManager* rm = AFGRecipeManager::Get(world);
	rm->GetAvailableRecipesForProducer(vanillaPacker, recipeCache);

	UE_LOG(LogTemp, Warning, TEXT("Updating smart packer recipe cache [ %d ] Recipes found"), recipeCache.Num());
}

void AABSmartPacker::FindRecipeFromInputs() {
	TSubclassOf<UFGItemDescriptor> foundFluid;
	TSubclassOf<UFGItemDescriptor> foundSolid;

	// fluid
	if (mPipeInputConnections.Num() > 0) {
		foundFluid = mPipeInputConnections[0]->GetFluidDescriptor();
	} else {
		foundFluid = nullptr;
	}
	
	// solid
	if (mFactoryInputConnections.Num() > 0) {
		TArray< FInventoryItem > peekResult;
		mFactoryInputConnections[0]->Factory_PeekOutput(peekResult, nullptr);
		foundSolid = peekResult.Num() == 0 ? nullptr : peekResult[0].ItemClass;
	} else {
		foundSolid = nullptr;
	}

	// filter
	if (foundFluid == currentFluidIn && foundSolid == currentSolidIn) { return; }

	currentFluidIn = foundFluid;
	currentSolidIn = foundSolid;

	UE_LOG(LogTemp, Warning, TEXT("INPUTS: %s - %s"), *UFGItemDescriptor::GetItemName(currentFluidIn).ToString(), *UFGItemDescriptor::GetItemName(currentSolidIn).ToString());

	if (currentSolidIn == nullptr) { return; }

	// recipe
	tryUpdateRecipeCache(GetWorld());
	bool assumePacking = currentFluidIn != nullptr;
	TSubclassOf<class UFGRecipe> foundRecipe = nullptr;

	for (int i = 0, l = recipeCache.Num(); i < l; i++) {
		UFGRecipe* examine = recipeCache[i].GetDefaultObject();
		TArray<FItemAmount>& ingredients = examine->mIngredients;

		if (assumePacking) {
			if (ingredients.Num() != 2) { continue; }

			if ((ingredients[0].ItemClass == currentFluidIn || ingredients[0].ItemClass == currentSolidIn) &&
				(ingredients[1].ItemClass == currentFluidIn || ingredients[0].ItemClass == currentSolidIn)) {
				foundRecipe = recipeCache[i];
				break;
			}
		} else {
			if (ingredients.Num() != 1) { continue; }

			if (ingredients[0].ItemClass == currentSolidIn) {
				foundRecipe = recipeCache[i];
				break;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("FOUND!: %s "), *UFGRecipe::GetRecipeName(foundRecipe).ToString());

	// set it
	if (foundRecipe != nullptr) {
		//empty the inventories!
		//empty the inventories!
		//empty the inventories!
		//empty the inventories!
		//empty the inventories!
		//empty the inventories!

		isLookingforRecipe = false;

		if (GetLocalRole() == ENetRole::ROLE_Authority) {
			SetRecipe(foundRecipe);
		}
	}
}

