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

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//no super
	auto TankForward = GetOwner()->GetActorForwardVector();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightThrow = FVector::CrossProduct(AIForwardIntention, TankForward);

	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow.Z);
	

	UE_LOG(LogTemp, Warning, TEXT("%f"), ForwardThrow)
}

