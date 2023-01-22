


#include "FPSAttributeSet.h"

UFPSAttributeSet::UFPSAttributeSet()
{

}

void UFPSAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	AFPSCharacter* FPSChar = Cast<AFPSCharacter>(GetOwningActor());

	if (Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->MaxHealth);
	if (Attribute == GetArmourAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->MaxArmour);
	if (Attribute == GetBulletAmmoAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->MaxBulletAmmo);
	if (Attribute == GetSpecialAmmoAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->MaxSpecialAmmo);
}

bool UFPSAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	float AbsolulteMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);

	AFPSCharacter* FPSChar = Cast<AFPSCharacter>(GetOwningActor());

	if (Data.EvaluatedData.Magnitude > 0)
	{
		//Addition in value
		if (Data.EvaluatedData.Attribute == GetArmourAttribute() && GetArmour() + AbsolulteMagnitude >= FPSChar->MaxArmour)
		{
			SetArmour(FPSChar->MaxArmour);
			return false;
		}

		else if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() + AbsolulteMagnitude >= FPSChar->MaxHealth)
		{
			SetHealth(FPSChar->MaxHealth);
			return false;
		}

		else if (Data.EvaluatedData.Attribute == GetBulletAmmoAttribute() && GetBulletAmmo() + AbsolulteMagnitude >= FPSChar->MaxBulletAmmo)
		{
			SetBulletAmmo(FPSChar->MaxBulletAmmo);
			return false;
		}

		else if (Data.EvaluatedData.Attribute == GetSpecialAmmoAttribute() && GetSpecialAmmo() + AbsolulteMagnitude >= FPSChar->MaxSpecialAmmo)
		{
			SetSpecialAmmo(FPSChar->MaxSpecialAmmo);
			return false;
		}
	}
	else if (Data.EvaluatedData.Magnitude < 0)
	{
		//Reduction in value
		if (Data.EvaluatedData.Attribute == GetArmourAttribute() && AbsolulteMagnitude > GetArmour())
		{
			Health.SetCurrentValue(GetHealth() - (AbsolulteMagnitude - GetArmour()));
		}
	}


	return true;
}

void UFPSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	//Prevent negative values
	if (Data.EvaluatedData.Attribute == GetArmourAttribute() && GetArmour() < 0)
	{
		SetArmour(0);
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() < 0)
	{
		SetHealth(0);
	}
	else if (Data.EvaluatedData.Attribute == GetBulletAmmoAttribute() && GetBulletAmmo() < 0)
	{
		SetBulletAmmo(0);
	}
	else if (Data.EvaluatedData.Attribute == GetSpecialAmmoAttribute() && GetSpecialAmmo() < 0)
	{
		SetSpecialAmmo(0);
	}
}
