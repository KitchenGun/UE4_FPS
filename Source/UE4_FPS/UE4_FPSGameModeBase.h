// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE4_FPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4_FPS_API AUE4_FPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;
};
