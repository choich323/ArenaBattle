// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h" // EngineMinimal.h 를 위해 include
#include "GameFramework/GameModeBase.h"
#include "ABGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	AABGameMode(); // 생성자 선언

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

};
