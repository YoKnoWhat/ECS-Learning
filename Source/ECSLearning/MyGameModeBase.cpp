// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "ECS/ECSEntity.h"
#include "ECS/ECSWorld.h"


void AMyGameModeBase::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

	FECSWorld* ECSWorldInst = FECSWorld::Instance();

	{
		FECSEntity* NewEntity = ECSWorldInst->CreateEntity();

		NewEntity->AddComponent(EECSComponentType::Test);
	}
}
