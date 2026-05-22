
#include "GAS/Ability/AFGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attributes/AFVitalAttributeSet.h"
#include "GAS/Attributes/AFPrimaryAttributeSet.h"

const UAFVitalAttributeSet* UAFGameplayAbility::GetVitalAttributeSet() const
{
	const UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC) return nullptr;

	return ASC->GetSet<UAFVitalAttributeSet>();
}

const UAFPrimaryAttributeSet* UAFGameplayAbility::GetPrimaryAttributeSet() const
{
	const UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC) return nullptr;

	return ASC->GetSet<UAFPrimaryAttributeSet>();
}
