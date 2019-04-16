// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"   
#include "TankAimingComponent.generated.h"


//Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//forward declaration : TO AVOID CHAIN OF DEPENDENCY
class GameplayStatics;

class UTankBarrel; 
class UTankTurret;
class AProjectile;

//Hold barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);


	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;


private:

	// Local Barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, category = "Firing")
	float LaunchSpeed = 5000.f;

		
	void MoveBarrelTowards(FVector AimDirection);

	void MoveTurretTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //SubclassOf is a template class that provides UClass type safety

	//UPROPERTY(EditAnywhere, category = Setup)     does not work... why?
		//AProjectile* adsf; 



	UPROPERTY(EditAnywhere, category = "Setup")
	float ReloadTimeInSeconds = 3.f;



	double LastFireTime = 0;


};
