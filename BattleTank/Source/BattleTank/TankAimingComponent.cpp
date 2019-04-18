// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"//WHEN YOU ACTUALLY 'USE THE FUNCTION' FROM THE OTHER FILE, YOU NEED TO INCLUDE HEADER FILE. IT'S NOT ENOUGH USING FORWARD DECLARATION.
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//so that initial fire delay
	LastFireTime = FPlatformTime::Seconds();

}
void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (ensure(BarrelToSet && TurretToSet)) 
	{
		Barrel = BarrelToSet;
		Turret = TurretToSet;
	}
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
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
		false,
		0.f, 
		0.f, 
		ESuggestProjVelocityTraceOption::DoNotTrace //NOT A BUG https://community.gamedev.tv/t/suggestprojectilevelocity-is-not-a-bug-working-as-intended-and-heres-why/79193
	);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OutLaunchVelocity.ToString())


	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal(); //this makes it unit vector. Gets a normalized copy of the vector, checking it is safe to do so based on the length. Returns zero vector if vector length is too small to safely normalize.
		
		MoveBarrelTowards(AimDirection);

		MoveTurretTowards(AimDirection);


		auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("Aim solution found"))
	}
	else
	{
	}
}


	void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
	{

		if (!ensure(Barrel && Turret)) { return; }
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - BarrelRotator;
		

			Barrel->Elevate(DeltaRotator.Pitch);
	}

	void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
	{

		auto TurretRotator = Turret->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - TurretRotator;
	

			if (FMath::Abs(DeltaRotator.Yaw) < 180)//!!! to avoid going the long-way round
			{
				Turret->Rotate(DeltaRotator.Yaw);
			}
			else
			{
				Turret->Rotate(-DeltaRotator.Yaw);
			}



	}



	void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
	{
		if (GetRoundsLeft() < 1)
		{
			FiringState = EFiringState::OutOfAmmo;

		}
		else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		{
			FiringState = EFiringState::Reloading;
		}
		else if (IsBarrelMoving())
		{
			FiringState = EFiringState::Aiming;
		}
		else
		{

			FiringState = EFiringState::Locked;
		}
	}

	bool UTankAimingComponent::IsBarrelMoving()
	{
		if (!ensure(Barrel)) { return false; }
		return !(Barrel->GetForwardVector().Equals(AimDirection, 0.1));//NEVER USE '=' on vector
	}

	void UTankAimingComponent::Fire()
	{
		
		if((FiringState != EFiringState::Reloading) && (FiringState != EFiringState::OutOfAmmo))
		{


	//		if (!ensure(Barrel && isReloaded && ProjectileBlueprint)) { return; }

			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))//StaticMeshComponent type has this kind of method
				);
			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();

			RoundsLeft--;//YOU CAN DO THIS!

		}

	}

	EFiringState UTankAimingComponent::GetFiringState() const
	{
		return FiringState;
	}

	int32 UTankAimingComponent::GetRoundsLeft() const
	{
		return RoundsLeft;
	}


	/*
	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();

	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString())
	*/
