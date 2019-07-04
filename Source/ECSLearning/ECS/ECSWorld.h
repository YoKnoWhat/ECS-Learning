
#include "Runtime/CoreUObject/Public/UObject/GCObject.h"
#include "Runtime/Core/Public/Containers/List.h"
#include "ECS/ECSComponent.h"


class FECSEntity;
class FECSSystemBase;

class FECSWorld
{
public:
	static FECSWorld* Instance();

	FECSWorld();

	~FECSWorld();

	// virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	   
	FECSEntity* CreateEntity();

	FECSEntity* FindEntity(uint32 UID)const;

	void DestroyEntity(FECSEntity* Entity);

	FECSSystemBase* GetSystem(EECSComponentType Type)const;

private:
	void Tick(float DeltaTime);

	void AllocateEntityChunk();

	void InitSystems();

private:
	const uint32 EntityChunkSize = 1024;
	uint32 CurrentUID = 0;

	TList<FECSEntity*> *EntityChunkHead;

	TArray<FECSEntity*> UnusedEntityPool;
	TMap<uint32, FECSEntity*> UsedEntityPool;

	TArray<FECSSystemBase*> SystemArray;
};