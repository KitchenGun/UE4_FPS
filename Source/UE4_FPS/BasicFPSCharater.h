// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicFPSCharater.generated.h"

UCLASS()
class UE4_FPS_API ABasicFPSCharater : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicFPSCharater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	void MoveForward(float a_fValue);
	void MoveRight(float a_fValue);
	FVector SpeedLimit(FVector a_moveDir);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	float fMoveForwardSpeed = 1.0f;
	float fMoveRightSpeed = 1.0f;
	bool bMoveForwardDir = false;

	FVector MovementDirection = FVector().ZeroVector;
};
