// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw * 2);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw * 2);
	RightTrack->SetThrottle(-Throw);

}
