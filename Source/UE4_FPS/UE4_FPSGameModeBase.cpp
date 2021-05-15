// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4_FPSGameModeBase.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

void AUE4_FPSGameModeBase::StartPlay()
{
    Super::StartPlay();

    if (GEngine)
    {
        // ����� �޽����� 5 �ʰ� ǥ���մϴ�.
        // "Ű" (ù ��° �μ�) ���� -1 �� �ϸ� �� �޽����� ���� ������Ʈ�ϰų� ���ΰ�ĥ �ʿ䰡 ������ ��Ÿ���ϴ�.
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
    }
}
