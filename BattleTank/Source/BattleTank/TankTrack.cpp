// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()//in order to make tick you need constructor first no return type on the constructor

{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); //OnComponentHit is delegate variable of FComponentHitSigniture
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) 
{
	UE_LOG(LogTemp, Warning, TEXT("ASDFH"))
}



void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);//is not required because this only calls blueprint node which mean no need when you don't use blueprint node!! inserting this is a good habit
	{
		auto Slippagespeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());//DotProduct does not care order of the argument which is different from CrossProduct.

		auto CorrectionAcceleration = -(Slippagespeed / DeltaTime) * GetRightVector();//acceleration is speed over time (speed/time) , this works out the required acceleration this frame to correct

		auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());//In order to get the physics(?) property

		auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; //two tracks
		TankRoot->AddForce(CorrectionForce);
	}
}





void UTankTrack::SetThrottle(float Throttle)
{

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;

	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
