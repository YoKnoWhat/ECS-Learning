
#include "ECS/ECSEntity.h"
#include "ECS/ECSWorld.h"
#include "ECS/ECSSystem.h"


FECSEntity::FECSEntity()
{}

FECSEntity::~FECSEntity()
{
	for (auto Iter = ComponentMap.CreateIterator(); Iter; Iter++)
	{
		FECSSystem *System;

		System->DestroyComponent(Iter.Value);
	}

	ComponentMap.Reset();
}

void FECSEntity::AddComponent(EECSComponentType Type)
{
	FECSSystem* System = FECSWorld::Instance()->GetSystem(Type);

	FECSComponent* NewComponent = System->NewComponent();
	ComponentMap.Add(Type, NewComponent);

}

void RemoveComponent()
{}
