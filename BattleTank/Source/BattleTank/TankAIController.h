// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"//to implement ondeath

#include "TankAIController.generated.h"


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 300.f;

private:

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;//this gets called when the pawn gets possessed ... it happens at different time other than constructor and beginplay(). constructor is too early, beginplay might happens before controller possesses pawn... want to happen only once.

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossessedTankDeath();
//	ATank* GetControlledTank() const;


//	ATank* GetPlayerTank() const;

	

};
