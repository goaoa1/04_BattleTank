// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;
/**
 * Responsible for driving the Tank Tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//this is not enough to get reference of the object in the editor
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);//Should be in public section because it needs to be called in blueprint


	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendTurnLeft(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendTurnRight(float Throw);


private:
	UTankTrack* LeftTrack = nullptr;//requirements of pointers and instaces are different
	UTankTrack* RightTrack = nullptr;
	
};
