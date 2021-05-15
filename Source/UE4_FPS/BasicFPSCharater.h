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
	void Turn(float a_fValue);
	void LookUp(float a_fValue);
	FVector SpeedLimit(FVector a_moveDir);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//�̵� ���� ����
	float m_fMoveForwardSpeed = 1.0f;
	float m_fMoveRightSpeed = 1.0f;
	bool m_bMoveForwardDir = false;//���������� Ȯ�ο� ����

	FVector m_VMovementDirection = FVector().ZeroVector;
	//�ü� ���� ����
	float m_fMouseSensitivity = 1.2f;//�ΰ���
};
