
#include "Player/AFForgerComponent.h"

#include "AbilitySystemInterface.h"
#include "EnhancedInputComponent.h"
#include "GAS/Ability/AFAbilitySet.h"


UAFForgerComponent::UAFForgerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UAFForgerComponent::InitializePlayerInput(UInputComponent* InputComponent)
{
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		for (const auto& [Action, Tag] : InputTagMap)
		{
			EIC->BindAction(Action, ETriggerEvent::Started, this,
				&UAFForgerComponent::TryActivateAbilityByInputTag, Tag);
		}
	}
}

void UAFForgerComponent::TryActivateAbilityByInputTag(FGameplayTag InputTag)
{
	if (!AbilitySet) return;

	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(GetOwner()))
	{
		UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
		AbilitySet->TryActivateAbilityByInputTag(ASC, InputTag);
	}
}

void UAFForgerComponent::GiveAbilities(UAbilitySystemComponent* ASC)
{
	if (!ASC || !AbilitySet) return;

	AbilitySet->GiveAbilities(ASC);
}


void UAFForgerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}
