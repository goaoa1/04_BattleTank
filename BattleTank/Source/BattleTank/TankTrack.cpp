// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()//in order to make tick you need constructor first no return type on the constructor

{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); //OnComponentHit is delegate variable of FComponentHitSigniture
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) //will be called almost every frame
{
	DriveTrack();

	ApplySideWaysForce();
	
	CurrentThrottle = 0;
}





void UTankTrack::ApplySideWaysForce()
{
	auto Slippagespeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());//DotProduct does not care order of the argument which is different from CrossProduct.

	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto CorrectionAcceleration = -(Slippagespeed / DeltaTime) * GetRightVector();//acceleration is speed over time (speed/time) , this works out the required acceleration this frame to correct

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());//In order to get the physics(?) property

	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; //two tracks
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -3, 3);//why -3? because i had less track power for both tracks ..
}


void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;

	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}