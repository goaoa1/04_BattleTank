// Fill out your copyright notice in the Description page of Project Settings.
/*
#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxleConstraint"));//at the moment editor starts
	SetRootComponent(MassAxleConstraint);


	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassAxleConstraint);
//	Axle->AttachToComponent(MassAxleConstraint, FAttachmentTransformRules::KeepWorldTransform);

	

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));

	//LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetupAttachment(Axle);//this is only possible in the constructor but is shorter and better
//	Wheel->AttachToComponent(AxleWheelConstraint, FAttachmentTransformRules::KeepWorldTransform);WheelConstraint

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
	//	AxleWheelConstraint->AttachToComponent(Axle, FAttachmentTransformRules::KeepWorldTransform);
	
	//Changing variable name might cause problem so make sure to turn the editor on and off.l..

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	SetupConstraint();

	//MassWheelConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(GetDefaultAttachComponent()), FName("Mass"), Wheel, FName("Wheel"));
}

//GetAttachParentActor()->FindComponentByClass<UTankTrack>()

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}


void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;

	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassAxleConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);//ATTACH TO ROOT(TANK) rather than track.... but spawn location is track which is set by spawnpoint

	//MassWheelConstraint->SetConstrainedComponents(Cast<UTankTrack>(GetDefaultAttachComponent()), FName("Mass"), Wheel, FName("Wheel")); this only finds root component. you should have looked for what and how it returns!!

	//MassWheelConstraint->SetConstrainedComponents(GetAttachParentActor()->FindComponentByClass<UTankTrack>(), FName("Mass"), Wheel, FName("Wheel"));

	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);


}


*/




// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}
