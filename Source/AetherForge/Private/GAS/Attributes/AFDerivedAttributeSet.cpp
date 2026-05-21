#include "AetherForge/Public/GAS/Attributes/AFDerivedAttributeSet.h"
#include "AetherForge.h"
#include "Net/UnrealNetwork.h"

UAFDerivedAttributeSet::UAFDerivedAttributeSet()
{
}

void UAFDerivedAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAFDerivedAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFDerivedAttributeSet, MagicPower,  COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFDerivedAttributeSet, Defense,     COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFDerivedAttributeSet, HitRate,     COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFDerivedAttributeSet, CritRate,    COND_None, REPNOTIFY_Always);
}

void UAFDerivedAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFDerivedAttributeSet, AttackPower, OldAttackPower);
}

void UAFDerivedAttributeSet::OnRep_MagicPower(const FGameplayAttributeData& OldMagicPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFDerivedAttributeSet, MagicPower, OldMagicPower);
}

void UAFDerivedAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFDerivedAttributeSet, Defense, OldDefense);
}

void UAFDerivedAttributeSet::OnRep_HitRate(const FGameplayAttributeData& OldHitRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFDerivedAttributeSet, HitRate, OldHitRate);
}

void UAFDerivedAttributeSet::OnRep_CritRate(const FGameplayAttributeData& OldCritRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFDerivedAttributeSet, CritRate, OldCritRate);
}

void UAFDerivedAttributeSet::RecalculateDerivedAttributes(const UAFPrimaryAttributeSet* PrimaryAS)
{
	const float Str  = PrimaryAS->GetStrength();
	const float Dex  = PrimaryAS->GetDexterity();
	const float Int_ = PrimaryAS->GetIntelligence();
	const float Vit  = PrimaryAS->GetVitality();

	SetAttackPower(Str  * 2.0f);
	SetMagicPower (Int_ * 2.0f);
	SetDefense    (Vit  * 1.5f + Str * 0.5f);
	SetHitRate    (Dex  * 1.0f);
	SetCritRate   (Dex  * 0.3f);

	PRINTLOG(TEXT("[Primary]   Str=%.1f  Dex=%.1f  Int=%.1f  Vit=%.1f"), Str, Dex, Int_, Vit);
	PRINTLOG(TEXT("[Derived]   AttackPower=%.1f  MagicPower=%.1f  Defense=%.1f  HitRate=%.1f  CritRate=%.1f"),
		GetAttackPower(), GetMagicPower(), GetDefense(), GetHitRate(), GetCritRate());
}
