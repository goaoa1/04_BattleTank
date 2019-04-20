// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

//Depends on movement component via pathfinding system



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	/*UE_LOG(LogTemp, Warning, TEXT("TankAIController BeginPlay"))


	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController can't find PlayerTank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player: %s"), *(PlayerTank->GetName()))
	}
*/

}

void ATankAIController::SetPawn(APawn * InPawn)//this gets called when the pawn gets possessed ... it happens at different time other than constructor and beginplay(). constructor is too early, beginplay might happens before controller possesses pawn... want to happen only once.
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);


	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("DEAD"))
	GetPawn()->DetachFromControllerPendingDestroy();
}



//ATank* ATankAIController::GetControlledTank() const //const is also a signiture
//{


	//return //you can set default pawn in the pawn blueprint!
//}

//ATank* ATankAIController::GetPlayerTank() const
//{
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


//}



void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!(PlayerTank && ControlledTank)) { return; } //if (!ensure(PlayerTank && ControlledTank)) { return; }-> does not take automotar in to account
	
	MoveToActor(PlayerTank, AcceptanceRadius);//!!

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();//'apawn' knows 'findcomponentbyclass' function

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	//GetComponentByClass simply calls FindComponentByClass and provides the UFUNCTION annotation so that it can be used from Blueprints. I believe the reason for doing this is that in newer versions of UE4, Epic tries to no longer expose virtual functions directly to Blueprints.
	


	//TODO fix below
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}


