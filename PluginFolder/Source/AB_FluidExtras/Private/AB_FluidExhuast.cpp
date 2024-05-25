// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_FluidExhuast.h"

void AAB_FluidExhuast::BeginPlay() {
	Super::BeginPlay();

	inputConnection = GetComponentByClass<UFGPipeConnectionFactory>();

	if (GetLocalRole() == ENetRole::ROLE_Authority) {
		if (mInputInventory == NULL) {
			mInputInventory = UFGInventoryLibrary::CreateInventoryComponent(this, "InputInventory");
			mInputInventory->AddArbitrarySlotSize(0, storageOverride);
		}

		inputConnection->SetInventory(mInputInventory);
		inputConnection->SetInventoryAccessIndex(0);
	}
}

//
TSubclassOf<class UFGItemDescriptor> AAB_FluidExhuast::GetCurrentVentItem() const {
	FInventoryStack stackTemp;
	if (mInputInventory->GetStackFromIndex(0, stackTemp)) {
		return stackTemp.Item.GetItemClass();
	}
	return NULL;
}

int AAB_FluidExhuast::GetStoredFluidCurrent() const {
	FInventoryStack stackTemp;
	if (mInputInventory->GetStackFromIndex(0, stackTemp)) {
		return stackTemp.NumItems;
	}
	return 0;
}

int AAB_FluidExhuast::GetVentRateCurrent() const {
	return 33123;
}

//
void AAB_FluidExhuast::Factory_Tick(float dt) {
	// investigate to see if we should pull fluid
	if (inputConnection->IsConnected()) {
		PullFluid(dt);
	}

	// handle venting of fluid we possess
	VentFluid(dt);
}

void AAB_FluidExhuast::PullFluid(float dt) {
	TSubclassOf<UFGItemDescriptor> foundFluidType = inputConnection->GetFluidDescriptor();

	if (foundFluidType == NULL) { return; }

	// if it's a new fluid wait until we're empty to pull
	if (foundFluidType != GetCurrentVentItem()) {
		if (bActiveVenting) { return; }

		// do we like our new fluid
		if (!isValidFluid(foundFluidType)) { return; }

		// clean out
		mInputInventory->RemoveAllFromIndex(0);
	}

	// perform pull
	FInventoryStack tempStack;
	inputConnection->Factory_PullPipeInput(dt, tempStack, foundFluidType, 10000);
}

void AAB_FluidExhuast::VentFluid(float dt) {
	if (mInputInventory->IsIndexEmpty(0)) { return; }
	
	//TODO: RATES
	int removalRate = 100;
	mInputInventory->RemoveFromIndex(0, removalRate);
}

bool AAB_FluidExhuast::isValidFluid(TSubclassOf<class UFGItemDescriptor> item) {
	if (safeItems.Num() == 0) { return true; }
	return safeItems.Contains(item);
}