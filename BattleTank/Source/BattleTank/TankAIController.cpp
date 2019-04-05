// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController BeginPlay"))


	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController can't find PlayerTank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player: %s"), *(PlayerTank->GetName()))
	}


}



ATank* ATankAIController::GetControlledTank() const //const is also a signiture
{


	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	/*
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	ATank* PlayerTank = TankPlayerController->GetControlledTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerTank"))
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Got PlayerTank"))
		return PlayerTank;
	}
	My way
	
	DIFFERENCE: THIS IS DONE AT COMPILE TIME 
	WHICH MEANS YOU NEED TO KNOW 'TANKPLAYERCONTROLLER' AT COMPILE TIME WHICH ALSO MEANS YOU NEED TO INSERT #include "TankPlayerController.h" ON THE HEADER FILE
	
	*/


	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);




}
