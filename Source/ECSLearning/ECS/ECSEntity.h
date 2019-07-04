
#include "Runtime/CoreUObject/Public/UObject/GCObject.h"
#include "ECS/ECSComponent.h"


class FECSEntity
{
	friend class FECSWorld;

public:
	FECSEntity();

	~FECSEntity();

	// virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	void AddComponent(EECSComponentType Type);

	void RemoveComponent();

	/** Property */
	FORCEINLINE uint32 GetUID()const
	{
		return UID;
	}

private:
	FORCEINLINE void SetUID(uint32 InUID)
	{
		UID = InUID;
	}

private:
	uint32 UID;

	TMap<EECSComponentType, FECSComponent*> ComponentMap;
};