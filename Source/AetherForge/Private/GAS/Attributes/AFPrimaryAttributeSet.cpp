#include "AetherForge/Public/GAS/Attributes/AFPrimaryAttributeSet.h"
#include "GAS/Attributes/AFDerivedAttributeSet.h"
#include "GAS/Attributes/AFVitalAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UAFPrimaryAttributeSet::UAFPrimaryAttributeSet()
{
}

void UAFPrimaryAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAFPrimaryAttributeSet, Strength,     COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFPrimaryAttributeSet, Dexterity,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFPrimaryAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFPrimaryAttributeSet, Vitality,     COND_None, REPNOTIFY_Always);
}

void UAFPrimaryAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFPrimaryAttributeSet, Strength, OldStrength);
}

void UAFPrimaryAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFPrimaryAttributeSet, Dexterity, OldDexterity);
}

void UAFPrimaryAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFPrimaryAttributeSet, Intelligence, OldIntelligence);
}

void UAFPrimaryAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFPrimaryAttributeSet, Vitality, OldVitality);
}

void UAFPrimaryAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute& ChangedAttr = Data.EvaluatedData.Attribute;

	const bool bIsPrimaryAttr =
		ChangedAttr == GetStrengthAttribute()     ||
		ChangedAttr == GetDexterityAttribute()    ||
		ChangedAttr == GetIntelligenceAttribute() ||
		ChangedAttr == GetVitalityAttribute();

	if (!bIsPrimaryAttr)
	{
		return;
	}

	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	const UAFDerivedAttributeSet* DerivedAS = ASC->GetSet<UAFDerivedAttributeSet>();
	if (DerivedAS)
	{
		const_cast<UAFDerivedAttributeSet*>(DerivedAS)->RecalculateDerivedAttributes(this);
	}

	const UAFVitalAttributeSet* VitalAS = ASC->GetSet<UAFVitalAttributeSet>();
	if (VitalAS)
	{
		const_cast<UAFVitalAttributeSet*>(VitalAS)->RecalculateVitalAttributes(this);
	}
}
