

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
		bMoveForwardDir = true;
	}
	else
	{
		bMoveForwardDir = false;
	}
	// ��� ���� �������� �˾Ƴ���, �÷��̾ �� �������� �̵��ϰ��� �Ѵٰ� ����մϴ�.
	FVector Direction = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::X);
	//�밢�� �ӵ� ��� ���� ��Ͽ� x�� �̵� ���
	MovementDirection.X = a_fValue * fMoveForwardSpeed;
	AddMovementInput(Direction, a_fValue *fMoveForwardSpeed);
	
}

void ABasicFPSCharater::MoveRight(float a_fValue)
{
	
	// ��� ���� �������� �˾Ƴ���, �÷��̾ �� �������� �̵��ϰ��� �Ѵٰ� ����մϴ�.
	FVector MoveDir = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::Y);
	if (!bMoveForwardDir)
	{
		AddMovementInput(MoveDir, a_fValue * fMoveRightSpeed);
	}
	else
	{
		//�밢�� �ӵ� ��� ���� ��Ͽ� y�� �̵� ���
		MovementDirection.Y = a_fValue * fMoveRightSpeed;
		MoveDir.Y*=abs(SpeedLimit(MovementDirection).Y);
		AddMovementInput(MoveDir, a_fValue * fMoveRightSpeed);
	}
	UE_LOG(LogTemp, Log, TEXT("%f"), MoveDir.Y);
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
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasicFPSCharater::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasicFPSCharater::MoveRight);
}

