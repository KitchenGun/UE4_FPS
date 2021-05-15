

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
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
}

void ABasicFPSCharater::MoveForward(float Value)
{ 
	// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록합니다.
	FVector Direction = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ABasicFPSCharater::MoveRight(float Value)
{
	// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록합니다.
	FVector Direction = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
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

