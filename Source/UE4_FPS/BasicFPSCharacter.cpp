

#include "BasicFPSCharacter.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ABasicFPSCharacter::ABasicFPSCharacter()
	:
	m_fMoveForwardSpeed(0.7f),
	m_fMoveRightSpeed(0.7f),
	m_bMoveForwardDir(false),
	m_VMovementDirection(FVector().ZeroVector),
	m_fMouseSensitivity(1.2f),
	m_nJumpCounter(0),
	m_nJumpMaxCounter(1),
	m_fJumpHeight(400.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//ī�޶� ���� �ڵ�
	// Create a first person camera component.
	m_oFPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(m_oFPSCameraComponent != nullptr);
	// Attach the camera component to our capsule component.
	m_oFPSCameraComponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	// Position the camera slightly above the eyes.
	m_oFPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));//BaseEyeHeight
	// Enable the pawn to control camera rotation.
	m_oFPSCameraComponent->bUsePawnControlRotation = true;
	//1��Ī mesh
	m_oFPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(m_oFPSMesh != nullptr);
	//�ڽſ��Ը� ���̵��� ����
	m_oFPSMesh->SetOnlyOwnerSee(true);
	m_oFPSMesh->SetupAttachment(m_oFPSCameraComponent);
	//�׸��� �����
	m_oFPSMesh->bCastDynamicShadow = false;
	m_oFPSMesh->CastShadow = false;
	//3��Ī �𵨸� �Ⱥ��̰� �ϱ�
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void ABasicFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// 5 �ʰ� ����� �޽����� ǥ���մϴ�. (ù �μ���) -1 "Key" ���� �� �޽����� ������Ʈ �Ǵ� ���ΰ�ĥ �ʿ䰡 ������ ��Ÿ���ϴ�.
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
}

void ABasicFPSCharacter::MoveForward(float a_fValue)
{ 
	//���� �̵������� Ȯ�ο�
	if (a_fValue != 0)//�Է��� ������ �������
	{
		m_bMoveForwardDir = true;
		// ��� ���� �������� �˾Ƴ���, �÷��̾ �� �������� �̵��ϰ��� �Ѵٰ� ����մϴ�.
		FVector MoveDir = this->GetActorForwardVector();
		//�밢�� �ӵ� ��� ���� ��Ͽ� x�� �̵� ���
		m_VMovementDirection.X = a_fValue * m_fMoveForwardSpeed;
		AddMovementInput(MoveDir, a_fValue * m_fMoveForwardSpeed);
	}
	else
	{
		m_bMoveForwardDir = false;
	}
}
void ABasicFPSCharacter::MoveRight(float a_fValue)
{
	if (a_fValue != 0)//�Է��� ������ �������
	{
		// ��� ���� �������� �˾Ƴ���, �÷��̾ �� �������� �̵��ϰ��� �Ѵٰ� ����մϴ�.
		FVector MoveDir = this->GetActorRightVector();
		if (!m_bMoveForwardDir)
		{
			AddMovementInput(MoveDir, a_fValue * m_fMoveRightSpeed);
		}
		else
		{
			//�밢�� �ӵ� ��� ���� ��Ͽ� y�� �̵� ���
			m_VMovementDirection.Y = a_fValue * m_fMoveRightSpeed;
			MoveDir *= abs(SpeedLimit(GetActorForwardVector()+ GetActorRightVector()).Y);
			AddMovementInput(MoveDir, a_fValue * m_fMoveRightSpeed);
		}
	}
}
FVector ABasicFPSCharacter::SpeedLimit(FVector a_moveDir)
{
	double numerator = sqrt(pow(abs(a_moveDir.X), 2) + pow(abs(a_moveDir.Y), 2));
	double denominator = (abs(a_moveDir.X) + abs(a_moveDir.Y));
	double velocityRatio = (numerator / denominator);
	return a_moveDir* velocityRatio;
}

void ABasicFPSCharacter::Turn(float a_fValue)
{
	AddControllerYawInput(a_fValue * m_fMouseSensitivity);
}
void ABasicFPSCharacter::LookUp(float a_fValue)
{
	AddControllerPitchInput(a_fValue * m_fMouseSensitivity);
}

void ABasicFPSCharacter::DoJump()
{//������ Ʃ�丮�� ����� �ƴ� �ٸ� ������� ����
	if (m_nJumpCounter < m_nJumpMaxCounter)
	{
		ACharacter::LaunchCharacter(FVector(0, 0, m_fJumpHeight),false,true);
		m_nJumpCounter++;
	}
}

void ABasicFPSCharacter::Landed(const FHitResult& Hit)
{//���鿡 ���� ��� 0���� ����
	m_nJumpCounter = 0;
}

void ABasicFPSCharacter::Fire()
{//���

}

// Called every frame
void ABasicFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasicFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//��ǲ ������Ʈ ������ ����
	check(PlayerInputComponent);
	//�̵�
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasicFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasicFPSCharacter::MoveRight);
	//�ü�
	PlayerInputComponent->BindAxis("Turn", this, &ABasicFPSCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasicFPSCharacter::LookUp);
	//����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasicFPSCharacter::DoJump);
	//���
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasicFPSCharacter::Fire);
}

