

#pragma once

#include "PooledObject.h"
#include "FPSObjectPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_PROJECT_API UFPSObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPSObjectPool();

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		APooledObject* SpawnPooledObject();

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		TSubclassOf<class APooledObject> PooledObjectSubclass;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		int PoolSize = 20;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		float PooledObjectLifeSpan = 0.0f;

	UFUNCTION()
		void OnPooledObjectDespawn(APooledObject* PoolActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<APooledObject*> ObjectPool;
	TArray<int> SpawnedPoolIndexes;
};
