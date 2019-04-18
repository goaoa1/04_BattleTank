// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"





float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;  //casting!
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect the pointers because it's adding in the constructor it's very likely to fail(added at construction)

//	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));//at the moment editor starts

	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component")); can do it differently


}

// Called when the game starts or when spawned Needed for BP begin play to run!
//void ATank::BeginPlay()
//{
//	Super::BeginPlay();// Called when the game starts or when spawned Needed for BP begin play to run!


//}
//this is called by the engine!!!!!!!!
float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)//this is called by the engine!!!!!!!!//this is called by the engine!!!!!!!!
{

	int32 DamahePoints = FPlatformMath::RoundToInt(DamageAmount); //!!!!!!!!!!
	int32 DamageToApply = FMath::Clamp<int>(DamageAmount, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("%i %i"), DamageToApply, CurrentHealth) //should be %i for int or won't work at all...





	return DamageToApply;


}


