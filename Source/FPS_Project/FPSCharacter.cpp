


#include "FPSCharacter.h"
#include "AbilitySystemComponent.h"
#include "FPSAttributeSet.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating and adding the compoents declared in the header to the character
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	Attributes = CreateDefaultSubobject<UFPSAttributeSet>("Attributes");
}

UAbilitySystemComponent* AFPSCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		//Initialise ability system component info
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		//apply default attributes
		if (DefaultAttributeEffect)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}

		//Give abilities
		if (HasAuthority())
		{
			for (TSubclassOf<UGameplayAbility>& StartUpAbility : DefaultAbilities)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartUpAbility.GetDefaultObject(), 1, 0));
			}
		}
	}
}



