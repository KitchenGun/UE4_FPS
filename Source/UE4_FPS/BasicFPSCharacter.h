// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "BasicFPSCharacter.generated.h"

/*UENUM()  ??? enum�� �� �ȵǴ��� �𸣰���
enum class State : uint8
{
	NONE = 0,
	SINGLE,
	BURST,
	AUTO,
};
*/
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
	//�̵�
	void MoveForward(float a_fValue);
	void MoveRight(float a_fValue);
	//�ü�
	void Turn(float a_fValue);
	void LookUp(float a_fValue);
	FVector SpeedLimit(FVector a_moveDir);
	//UFUNCTION�� �������Ʈ�� ������ �ϰ� ���ش�
	UFUNCTION()
	void DoJump();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//�̵� ���� ����
	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
	float m_fMoveForwardSpeed;
	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
	float m_fMoveRightSpeed;
	bool m_bMoveForwardDir;//���������� Ȯ�ο� ����

	FVector m_VMovementDirection;
	//�ü� ���� ����
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float m_fMouseSensitivity;//�ΰ���
	//���� ���� ����
	int m_nJumpCounter;
	UPROPERTY(EditAnywhere, Category = "Jump")
	int m_nJumpMaxCounter;
	UPROPERTY(EditAnywhere, Category = "Jump")
	float m_fJumpHeight;
	//ī�޶� 
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* m_oFPSCameraComponent;
	//����Ī mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* m_oFPSMesh;
	//��� ���� 
	//���
	bool m_isReadyFire;
	float m_fRPM;
	float m_fVerticalRecoil;
	float m_fHorizontalRecoil;
	//����
	float m_fADSSpeed;
	//������
	//State m_eGunState;
	//źâ

	int m_nBullet;
	float m_fDamage;

};
