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


	


protected:



//	UPROPERTY(BlueprintReadOnly)//this makes the reference be read by editor
//	UTankMovementComponent* TankMovementComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;

	
	


};
