

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "FPSCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "FPSAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class FPS_PROJECT_API UFPSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UFPSAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Armour;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, Armour);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData BulletAmmo;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, BulletAmmo);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData SpecialAmmo;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, SpecialAmmo);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
