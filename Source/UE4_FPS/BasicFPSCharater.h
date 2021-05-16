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
	//이동
	void MoveForward(float a_fValue);
	void MoveRight(float a_fValue);
	//시선
	void Turn(float a_fValue);
	void LookUp(float a_fValue);
	FVector SpeedLimit(FVector a_moveDir);
	//UFUNCTION은 블루프린트에 접근을 하게 해준다
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void StopJump();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//이동 관련 변수
	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
	float m_fMoveForwardSpeed;
	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
	float m_fMoveRightSpeed;
	bool m_bMoveForwardDir;//전진중인지 확인용 변수

	FVector m_VMovementDirection;
	//시선 관련 변수
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float m_fMouseSensitivity;//민감도
};
