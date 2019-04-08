// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);//Clamp function is static which means it won't change what it receives but in this case it puts back the output into the input.
	auto RotationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds; //deltatimeseconds is independent of framerate

	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;//RawNewElevation doesn't go higher than 90... why? pitch won't go higher than 90... anything else is normal...

	auto Rotation = RawNewRotation;//just to be consistent with barrel

//	auto Rotation = FMath::Clamp<float>(RawNewRotation, MinRotationDegrees, MaxRotationDegrees);//what is clamped is 'elevation' not rawnewelevation. Clamp function is static which means it won't change what it receives.



	SetRelativeRotation(FRotator(0, Rotation, 0));


}


