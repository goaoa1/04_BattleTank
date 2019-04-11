// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "TankAimingComponent.h"  //needs only forward declaration here but needed in cpp
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();


protected:
	UTankAimingComponent* TankAimingComponent = nullptr;


	UPROPERTY(BlueprintReadOnly)//this makes the reference be read by editor
	UTankMovementComponent* TankMovementComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, category = Firing)
	float LaunchSpeed = 5000.f; 

	UPROPERTY(EditDefaultsOnly, category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; //SubclassOf is a template class that provides UClass type safety

	//UPROPERTY(EditAnywhere, category = Setup)     does not work... why?
		//AProjectile* adsf; 

	// Local Barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, category = Setup)
	float ReloadTimeInSeconds = 3.f;
	
	double LastFireTime = 0;
};
