// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "BasicFPSCharacter.generated.h"

UCLASS()
class UE4_FPS_API ABasicFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicFPSCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Fire();
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
	void DoJump();


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
	//점프 관련 변수
	int m_nJumpCounter;
	UPROPERTY(EditAnywhere, Category = "Jump")
	int m_nJumpMaxCounter;
	UPROPERTY(EditAnywhere, Category = "Jump")
	float m_fJumpHeight;
	//카메라 
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* m_oFPSCameraComponent;
	//일인칭 mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* m_oFPSMesh;
	//사격 제작 

};
