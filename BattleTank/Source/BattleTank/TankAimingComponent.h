// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"   
#include "TankAimingComponent.generated.h"


//Enum for aiming state
UENUM()
enum class EFiringState : uint8//THIS UINT8 IS IMPORTANT
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
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

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);


	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable)
	int32 GetRoundsLeft() const;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(BlueprintReadOnly)
	float AmmoLeft = 3;//SHOULD USE GETTER INSTEAD

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 RoundsLeft = 3;//int32 is platform independent. uint32 is not compatible to blueprint


private:

	// Local Barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000.f;

		
	void MoveBarrelTowards(FVector AimDirection);

	void MoveTurretTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //SubclassOf is a template class that provides UClass type safety

	//UPROPERTY(EditAnywhere, category = Setup)     does not work... why?
		//AProjectile* adsf; 

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ReloadTimeInSeconds = 3.f;

	double LastFireTime = 0;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;//BUG?

	bool IsBarrelMoving();

	FVector AimDirection;


};
