// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"




class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;//Blueprint is subclass of this C++ so it can't be in the private section but in the protected section

private:
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OUTHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	FVector GetReachLineStart();

	FVector GetReachLineEnd();

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	
};
