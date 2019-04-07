// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#define OUT

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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const //const is also a signiture
{
	

	return Cast<ATank>(GetPawn());//you can set the player's pawn in the game mode blueprint!!!
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //OUT Parameter
	if(GetSightRayHitLocation(HitLocation)) 
	{
		GetControlledTank()->AimAt(HitLocation);//if this was a reference it might be lost....
	}


}
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);


	//De-project the scteen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	
	//Line-trace along that look direction, and see what we hit (up to max range)
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; //To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);//don't forget to return the value when the function is not a void function!
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); //!!
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange); //!!!!!
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)//other parameters are set by default!!!!  ADVANCED OPTIONS ARE MAYBE HIDDEN...?
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;

}
























/*

bool ATankPlayerController::GetLookVectorHitLocation(float LineTraceRange, FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	//Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetPawn());         //it is a struct so what inside the () are constructor parms
	FCollisionResponseParams ResponseParameters(ECollisionResponse::ECR_Ignore);

	return GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		ECollisionChannel::ECC_Visibility, //Enum needs ::?
		TraceParameters
		ResponseParameters
	);
	
}


FVector ATankPlayerController::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(      //bit a strange function in that it takes reference and sets the value to it and returns void.
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FVector ATankPlayerController::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(      //bit a strange function in that it takes reference and sets the value to it and returns void.
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * LineTraceRange;
}


*/