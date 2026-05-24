
#include "GAS/Ability/AFAbilitySet.h"
#include "AetherForge.h"
#include "AbilitySystemComponent.h"
#include "GAS/Ability/AFGameplayAbility.h"

void UAFAbilitySet::GiveAbilities(UAbilitySystemComponent* ASC)
{
	if (!ASC) return;

	PRINTLOG(TEXT("GiveAbilities called, count: %d"), GrantedAbilities.Num());

	for (const auto& Ability : GrantedAbilities)
	{
		if (!Ability.AbilityClass) continue;

		FGameplayAbilitySpec Spec(Ability.AbilityClass, 1);
		Spec.GetDynamicSpecSourceTags().AddTag(Ability.InputTag);

		FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
		InputTagToHandle.Add(Ability.InputTag, Handle);

		PRINTLOG(TEXT("GiveAbility: %s, InputTag: %s"), *Ability.AbilityClass->GetName(), *Ability.InputTag.ToString());
	}
}

void UAFAbilitySet::TakeAbilities(UAbilitySystemComponent* ASC)
{
	if (!ASC) return;

	for (const auto& [Tag, Handle] : InputTagToHandle)
	{
		ASC->ClearAbility(Handle);
	}

	InputTagToHandle.Empty();
}

void UAFAbilitySet::TryActivateAbilityByInputTag(UAbilitySystemComponent* ASC, FGameplayTag InputTag)
{
	if (!ASC)
	{
		PRINTLOG(TEXT("ASC null"));
		return;
	}

	if (FGameplayAbilitySpecHandle* Handle = InputTagToHandle.Find(InputTag))
	{
		if (!Handle) return;
		ASC->TryActivateAbility(*Handle);
		PRINTLOG(TEXT("Ability Activated"));
	}
}
