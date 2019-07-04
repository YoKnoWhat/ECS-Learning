

#include "Runtime/Core/Public/Containers/ChunkedArray.h"

#include "ECS/Test/ECSTestComponent.h"


class FECSComponent;

template<class ElemType, uint32 TargetBytesPerChunk = 16384>
class FECSSystem : public FECSSystemBase
{
public:
	FECSComponent* NewComponent()
	{
		return &ChunkedArray[ChunkedArray.Add(1)];
	}

	void DestroyComponent(FECSComponent* Component);

private:
	TChunkedArray<ElemType, TargetBytesPerChunk> ChunkedArray;
};

class FECSSystemBase
{
public:
	FECSComponent* NewComponent()
	{}

	virtual void Tick(float DeltaTime) = 0;
};