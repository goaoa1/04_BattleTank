// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"


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

	virtual void Tick(float DeltaTime) override;


//	ATank* GetControlledTank() const;


//	ATank* GetPlayerTank() const;

	

};
