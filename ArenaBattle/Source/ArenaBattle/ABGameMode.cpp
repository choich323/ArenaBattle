// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ABPawn.h"
#include "ABPlayerController.h"

AABGameMode::AABGameMode::AABGameMode()  // ���λ�
{
	DefaultPawnClass = AABPawn::StaticClass(); // �⺻ �� Ŭ���� ����
	PlayerControllerClass = AABPlayerController::StaticClass();
}

void AABGameMode::PostLogin(APlayerController* NewPlayer) {
	UE_LOG(LogTemp, Warning, TEXT("PostLoginBegin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("PostLoginEnd"));
}