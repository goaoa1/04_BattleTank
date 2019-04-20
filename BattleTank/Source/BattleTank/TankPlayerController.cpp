// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

//	C++ BeginPlay works even if you have no BeginPlay BP in the editor

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();//the red underline does not matter
	if (!ensure(AimingComponent)) { return; }
	{
		FoundAimingComponent(AimingComponent);//This is broadcasting the event...?
	}
	

}

void ATankPlayerController::SetPawn(APawn * InPawn)//this gets called when the pawn gets possessed ... it happens at different time other than constructor and beginplay(). constructor is too early, beginplay might happens before controller possesses pawn... want to happen only once.
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);


	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}




void ATankPlayerController::Tick(float DeltaTime)
{
	if (!GetPawn()) { return; }
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}



void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation; //OUT Parameter


	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if(bGotHitLocation)
	{
		AimingComponent->AimAt(HitLocation);
//		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);//if this was a reference it might be lost....
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
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	
	//Line-trace along that look direction, and see what we hit (up to max range)
	
	return false;
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
		ECollisionChannel::ECC_Camera)//ECC_Visibility might hit UI)
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