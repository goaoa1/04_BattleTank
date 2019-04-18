// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "TankAimingComponent.h"  //needs only forward declaration here but needed in cpp
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	//called by the engine when actor damage is dealt
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	
	

	UFUNCTION(BlueprintPure, Category = "Health")//does not affect the owning object in any way and can be executed in a blueprint o level blueprint graph. like const
	float GetHealthPercent() const;//Returns current health as a percentage of starting health, between 0 and 1!!!!!

protected:



//	UPROPERTY(BlueprintReadOnly)//this makes the reference be read by editor
//	UTankMovementComponent* TankMovementComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
	


};
