// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_FluidExhuast.h"

void AAB_FluidExhuast::BeginPlay() {
	Super::BeginPlay();

	inputConnection = GetComponentByClass<UFGPipeConnectionFactory>();

	if (GetLocalRole() == ENetRole::ROLE_Authority) {
		if (mInputInventory == NULL) {
			mInputInventory = UFGInventoryLibrary::CreateInventoryComponent(this, "InputInventory");
		}

		inputConnection->SetInventory(mInputInventory);
	}
}

//
TSubclassOf<class UFGItemDescriptor> AAB_FluidExhuast::GetCurrentVentItem() const {
	return validItems[0];
}

int AAB_FluidExhuast::GetVentRateCurrent() const {
	return 33123;
}

int AAB_FluidExhuast::GetStoredFluidCurrent() const {
	return 42500;
}

//
void AAB_FluidExhuast::Factory_Tick(float dt) {
	//Super::Factory_Tick(dt);

	//UE_LOG(LogTemp, Warning, TEXT("MAH TOK"));
	//UE_LOG(LogTemp, Warning, TEXT("MAH JUICE [ %s"), *UFGItemDescriptor::GetItemName(foundFluidType).ToString());

	//mInputInventory->GetStackFromIndex

	//bool bSuccess = inputConnection->Factory_Internal_PullPipeInput(dt, FInventoryStack & out_stack, GetCurrentVentItem());

	// investigate to see if we should pull fluid
	if (inputConnection->IsConnected()) {
		PullFluid();
	}

	// handle venting of fluid we possess
	VentFluid();
}

void AAB_FluidExhuast::PullFluid() {
	TSubclassOf<UFGItemDescriptor> foundFluidType = inputConnection->GetFluidDescriptor();

	if (foundFluidType == NULL) { return; }

	// if it's a new fluid wait until we're empty to pull
	if (foundFluidType != GetCurrentVentItem()) {
		if (bActiveVenting) { return; }

		// swap fluid type
	}

	// perform pull
}

void AAB_FluidExhuast::VentFluid() {
}