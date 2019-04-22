// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()//in order to make tick you need constructor first no return type on the constructor

{
	PrimaryComponentTick.bCanEverTick = false;
}
/*
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
//	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); //OnComponentHit is delegate variable of FComponentHitSigniture
}
*/

/*

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) //will be called almost every frame
{
	DriveTrack();

	ApplySideWaysForce();
	
	CurrentThrottle = 0;
}

*/

/*
CAN DO THIS USING WHEEL CONSTRAINTS
void UTankTrack::ApplySideWaysForce()
{
	auto Slippagespeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());//DotProduct does not care order of the argument which is different from CrossProduct.

	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto CorrectionAcceleration = -(Slippagespeed / DeltaTime) * GetRightVector();//acceleration is speed over time (speed/time) , this works out the required acceleration this frame to correct

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());//In order to get the physics(?) property

	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; //two tracks
	TankRoot->AddForce(CorrectionForce);
}

*/

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -3, 3);//why -3? because i had less track power for both tracks .. CurrentThrottle + Throttle
	DriveTrack(CurrentThrottle);

}


void UTankTrack::DriveTrack(float CurrentThrottle)
{
//	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;

//	auto ForceLocation = GetComponentLocation();

//	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
//	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);


	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;

	auto Wheels = GetWheels();

	auto ForcePerWheel = ForceApplied / Wheels.Num();


	for (ASprungWheel* Wheel : Wheels)
	{

		//PROBLEM
		Wheel->AddDrivingForce(ForcePerWheel);

	}

}

TArray<ASprungWheel*> UTankTrack::GetWheels() const		//CONST is also a signiture !
{
	TArray<ASprungWheel*> ResultArray;

	TArray<USceneComponent*> Children;

	GetChildrenComponents(true, Children);

	for (UObject* Child : Children)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Child->GetName())//ONLY MassAxleConstraint

		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue; //Not RETURN HERE. WE WANT TO KEEP GOING!!!!!! CONTINUE !!!


		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();//!!!! get spawned actor

		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);

	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), ResultArray.Num())
	//Num is 0 situation

	return ResultArray;
}

	