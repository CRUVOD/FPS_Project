

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPS_PROJECT_API AFPSCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
		class UFPSAttributeSet* Attributes;

public:
	// Sets default values for this character's properties
	AFPSCharacter();

	//Override IAbilitySystemInterface interface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes");
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes");
	int MaxArmour = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes");
	int MaxBulletAmmo = 250;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes");
	int MaxSpecialAmmo = 15;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Effect that initialises default attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "FPS")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
	//Array of starting abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "FPS")
		TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;
};
