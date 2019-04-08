// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"//WHEN YOU ACTUALLY 'USE THE FUNCTION' FROM THE OTHER FILE, YOU NEED TO INCLUDE HEADER FILE. IT'S NOT ENOUGH USING FORWARD DECLARATION.
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity//'::' because it is static function!! UGameStatics is for blueprint so need to manually include header in the header file.
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		//false, default
		//0.f, 
		//0.f, 
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //this makes it unit vector. Gets a normalized copy of the vector, checking it is safe to do so based on the length. Returns zero vector if vector length is too small to safely normalize.
		MoveBarrelTowards(AimDirection);

		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s is Aiming at %s"), *TankName, *AimDirection.ToString())
	}
}


	void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
	{
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - BarrelRotator;
		

			Barrel->Elevate(5);
	}

	/*
	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();

	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString())
	*/
