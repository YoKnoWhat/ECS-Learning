
#include "ECS/ECSSystem.h"


class FECSTestSystem : public FECSSystem<FECSTestComponent>
{
public:
	virtual void Tick(float DeltaTime) override;
};