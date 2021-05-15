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
	void MoveForward(float Value);
	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	float fMoveForwardSpeed = 10.0f;
	float fMoveRightSpeed = 7.0f;

	FVector2D MoveVector = FVector2D().ZeroVector;
};
