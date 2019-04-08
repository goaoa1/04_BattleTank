// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);//Clamp function is static which means it won't change what it receives but in this case it puts back the output into the input.
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds; //deltatimeseconds is independent of framerate

	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;//RawNewElevation doesn't go higher than 90... why? pitch won't go higher than 90... anything else is normal...



	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);//what is clamped is 'elevation' not rawnewelevation. Clamp function is static which means it won't change what it receives.



	SetRelativeRotation(FRotator(Elevation, 0, 0));


}


 