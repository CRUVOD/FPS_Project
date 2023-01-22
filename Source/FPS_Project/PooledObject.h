//A

#pragma once

#include "PooledObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, APooledObject*, PoolActor);

UCLASS()
class FPS_PROJECT_API APooledObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooledObject();

	FOnPooledObjectDespawn OnPooledObjectDespawn;

	UFUNCTION(BlueprintCallable, Category = "Pooled Object")
		void Deactivate();

	void SetActive(bool IsActive);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int Index);

	bool IsActive();
	int GetPoolIndex();

protected:

	bool Active;
	float LifeSpan = 0.0f;
	int PoolIndex;

	FTimerHandle LifeSpanTimer;
};
