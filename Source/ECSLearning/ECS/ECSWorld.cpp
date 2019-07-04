
#include "ECS/ECSWorld.h"
#include "ECS/ECSEntity.h"
#include "ECS/ECSSystem.h"
#include "Public.h"


FECSWorld* FECSWorld::Instance()
{
	static FECSWorld Inst;
	return &Inst;
}

FECSWorld::FECSWorld() :
	EntityChunkHead(nullptr)
{
	InitSystems();

	AllocateEntityChunk();
}

FECSWorld::~FECSWorld()
{
	do
	{
		TList<FECSEntity*>* CurrentChunk = EntityChunkHead;

		delete[] CurrentChunk->Element;

		EntityChunkHead = CurrentChunk->Next;

		delete CurrentChunk;
	} while (EntityChunkHead != nullptr);

	CurrentUID = 0;
}

FECSEntity* FECSWorld::CreateEntity()
{
	if (UnusedEntityPool.Num() == 0)
	{
		AllocateEntityChunk();
	}
	
	FECSEntity* NewEntity = UnusedEntityPool.Last();
	UnusedEntityPool.SetNum(UnusedEntityPool.Num() - 1);

	UsedEntityPool.Add(NewEntity->GetUID(), NewEntity);

	return NewEntity;
}

FECSEntity* FECSWorld::FindEntity(uint32 UID)const
{
	FECSEntity* const* EntityPtr = UsedEntityPool.Find(UID);

	if (EntityPtr == nullptr)
	{
		return nullptr;
	}
	else
	{
		return *EntityPtr;
	}
}

void FECSWorld::DestroyEntity(FECSEntity* Entity)
{
	UsedEntityPool.Remove(Entity->GetUID());

	UnusedEntityPool.Add(Entity);
}

FECSSystemBase* FECSWorld::GetSystem(EECSComponentType Type)const
{
	return SystemArray[CastToUnderlyingType(Type)];
}

void FECSWorld::Tick(float DeltaTime)
{
	for (FECSSystemBase* System : SystemArray)
	{
		System->Tick(DeltaTime);
	}
}

void FECSWorld::AllocateEntityChunk()
{
	EntityChunkHead = new TList<FECSEntity*>(new FECSEntity[EntityChunkSize], EntityChunkHead);

	UnusedEntityPool.SetNum(EntityChunkSize);

	for (uint32 i = 0; i < EntityChunkSize; ++i)
	{
		FECSEntity *NewEntity = EntityChunkHead->Element + i;

		NewEntity->SetUID(CurrentUID++);

		UnusedEntityPool[i] = NewEntity;
	}
}

void FECSWorld::InitSystems();
