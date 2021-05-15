

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
		// 5 초간 디버그 메시지를 표시합니다. (첫 인수인) -1 "Key" 값은 이 메시지를 업데이트 또는 새로고칠 필요가 없음을 나타냅니다.
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
}

void ABasicFPSCharater::MoveForward(float a_fValue)
{ 
	//전진 이동중인지 확인용
	if (a_fValue != 0)
	{
		bMoveForwardDir = true;
	}
	else
	{
		bMoveForwardDir = false;
	}
	// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록합니다.
	FVector Direction = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::X);
	//대각선 속도 제어를 위한 기록용 x축 이동 기록
	MovementDirection.X = a_fValue * fMoveForwardSpeed;
	AddMovementInput(Direction, a_fValue *fMoveForwardSpeed);
	
}

void ABasicFPSCharater::MoveRight(float a_fValue)
{
	
	// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록합니다.
	FVector MoveDir = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::Y);
	if (!bMoveForwardDir)
	{
		AddMovementInput(MoveDir, a_fValue * fMoveRightSpeed);
	}
	else
	{
		//대각선 속도 제어를 위한 기록용 y축 이동 기록
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

