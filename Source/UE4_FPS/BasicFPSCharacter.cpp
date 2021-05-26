

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
	//카메라 관련 코드
	// Create a first person camera component.
	m_oFPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(m_oFPSCameraComponent != nullptr);
	// Attach the camera component to our capsule component.
	m_oFPSCameraComponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	// Position the camera slightly above the eyes.
	m_oFPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));//BaseEyeHeight
	// Enable the pawn to control camera rotation.
	m_oFPSCameraComponent->bUsePawnControlRotation = true;
	//1인칭 mesh
	m_oFPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(m_oFPSMesh != nullptr);
	//자신에게만 보이도록 제작
	m_oFPSMesh->SetOnlyOwnerSee(true);
	m_oFPSMesh->SetupAttachment(m_oFPSCameraComponent);
	//그림자 지우기
	m_oFPSMesh->bCastDynamicShadow = false;
	m_oFPSMesh->CastShadow = false;
	//3인칭 모델링 안보이게 하기
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void ABasicFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// 5 초간 디버그 메시지를 표시합니다. (첫 인수인) -1 "Key" 값은 이 메시지를 업데이트 또는 새로고칠 필요가 없음을 나타냅니다.
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
}

void ABasicFPSCharacter::MoveForward(float a_fValue)
{ 
	//전진 이동중인지 확인용
	if (a_fValue != 0)//입력이 없으면 실행안함
	{
		m_bMoveForwardDir = true;
		// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록합니다.
		FVector MoveDir = this->GetActorForwardVector();
		//대각선 속도 제어를 위한 기록용 x축 이동 기록
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
	if (a_fValue != 0)//입력이 없으면 실행안함
	{
		// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록합니다.
		FVector MoveDir = this->GetActorRightVector();
		if (!m_bMoveForwardDir)
		{
			AddMovementInput(MoveDir, a_fValue * m_fMoveRightSpeed);
		}
		else
		{
			//대각선 속도 제어를 위한 기록용 y축 이동 기록
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
{//기존의 튜토리얼 방식이 아닌 다른 방식으로 구현
	if (m_nJumpCounter < m_nJumpMaxCounter)
	{
		ACharacter::LaunchCharacter(FVector(0, 0, m_fJumpHeight),false,true);
		m_nJumpCounter++;
	}
}

void ABasicFPSCharacter::Landed(const FHitResult& Hit)
{//지면에 닿을 경우 0으로 만듬
	m_nJumpCounter = 0;
}

void ABasicFPSCharacter::Fire()
{//사격

}

// Called every frame
void ABasicFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasicFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//인풋 컴포넌트 없을시 종료
	check(PlayerInputComponent);
	//이동
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasicFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasicFPSCharacter::MoveRight);
	//시선
	PlayerInputComponent->BindAxis("Turn", this, &ABasicFPSCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasicFPSCharacter::LookUp);
	//점프
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasicFPSCharacter::DoJump);
	//사격
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasicFPSCharacter::Fire);
}

