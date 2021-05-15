

#include "BasicFPSCharater.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
ABasicFPSCharater::ABasicFPSCharater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasicFPSCharater::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// 5 �ʰ� ����� �޽����� ǥ���մϴ�. (ù �μ���) -1 "Key" ���� �� �޽����� ������Ʈ �Ǵ� ���ΰ�ĥ �ʿ䰡 ������ ��Ÿ���ϴ�.
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
}

void ABasicFPSCharater::MoveForward(float a_fValue)
{ 
	//���� �̵������� Ȯ�ο�
	if (a_fValue != 0)
	{
		m_bMoveForwardDir = true;
	}
	else
	{
		m_bMoveForwardDir = false;
	}
	// ��� ���� �������� �˾Ƴ���, �÷��̾ �� �������� �̵��ϰ��� �Ѵٰ� ����մϴ�.
	FVector Direction = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::X);
	//�밢�� �ӵ� ��� ���� ��Ͽ� x�� �̵� ���
	m_VMovementDirection.X = a_fValue * m_fMoveForwardSpeed;
	AddMovementInput(Direction, a_fValue *m_fMoveForwardSpeed);
	
}

void ABasicFPSCharater::MoveRight(float a_fValue)
{
	
	// ��� ���� �������� �˾Ƴ���, �÷��̾ �� �������� �̵��ϰ��� �Ѵٰ� ����մϴ�.
	FVector MoveDir = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::Y);
	if (!m_bMoveForwardDir)
	{
		AddMovementInput(MoveDir, a_fValue * m_fMoveRightSpeed);
	}
	else
	{
		//�밢�� �ӵ� ��� ���� ��Ͽ� y�� �̵� ���
		m_VMovementDirection.Y = a_fValue * m_fMoveRightSpeed;
		MoveDir.Y*=abs(SpeedLimit(m_VMovementDirection).Y);
		AddMovementInput(MoveDir, a_fValue * m_fMoveRightSpeed);
	}
}

void ABasicFPSCharater::Turn(float a_fValue)
{
	UE_LOG(LogTemp, Log, TEXT("Turn %f   ms%f"), a_fValue * m_fMouseSensitivity, m_fMouseSensitivity);
	AddControllerYawInput(a_fValue * m_fMouseSensitivity);
}

void ABasicFPSCharater::LookUp(float a_fValue)
{
	UE_LOG(LogTemp, Log, TEXT("LookUp %f"), a_fValue * m_fMouseSensitivity);
	AddControllerPitchInput(a_fValue * m_fMouseSensitivity);
}

FVector ABasicFPSCharater::SpeedLimit(FVector a_moveDir)
{
	double numerator = sqrt(pow(abs(a_moveDir.X), 2) + pow(abs(a_moveDir.Y), 2));
	double denominator = (abs(a_moveDir.X) + abs(a_moveDir.Y));
	double velocityRatio = (numerator / denominator);
	return a_moveDir* velocityRatio;
}

// Called every frame
void ABasicFPSCharater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// Called to bind functionality to input
void ABasicFPSCharater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//�̵�
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasicFPSCharater::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasicFPSCharater::MoveRight);
	//�ü�
	PlayerInputComponent->BindAxis("Turn", this, &ABasicFPSCharater::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasicFPSCharater::LookUp);
}

