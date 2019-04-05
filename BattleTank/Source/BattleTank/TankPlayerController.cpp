// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"




ATank* ATankPlayerController::GetControlledTank() const //const is also a signiture
{
	return Cast<ATank>(GetPawn());
}