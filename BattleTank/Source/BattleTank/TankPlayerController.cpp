// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay"))


	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController has no pawn"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController has pawn %s"), *(ControlledTank->GetName()))
	}
}



ATank* ATankPlayerController::GetControlledTank() const //const is also a signiture
{
	

	return Cast<ATank>(GetPawn());
}