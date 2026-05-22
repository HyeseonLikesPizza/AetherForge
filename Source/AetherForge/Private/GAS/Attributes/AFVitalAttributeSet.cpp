#include "AetherForge/Public/GAS/Attributes/AFVitalAttributeSet.h"
#include "AetherForge.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAFVitalAttributeSet::UAFVitalAttributeSet()
{
}

void UAFVitalAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAFVitalAttributeSet, Health,     COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFVitalAttributeSet, MaxHealth,  COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFVitalAttributeSet, Mana,       COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFVitalAttributeSet, MaxMana,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFVitalAttributeSet, Stamina,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAFVitalAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UAFVitalAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
}

void UAFVitalAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		PRINTLOG(TEXT("[Vital]   Health=%.1f / MaxHealth=%.1f"), GetHealth(), GetMaxHealth());
		// TODO: 체력 0 이하 시 사망 처리
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
		PRINTLOG(TEXT("[Vital]   Mana=%.1f / MaxMana=%.1f"), GetMana(), GetMaxMana());
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
		PRINTLOG(TEXT("[Vital]   Stamina=%.1f / MaxStamina=%.1f"), GetStamina(), GetMaxStamina());
	}
}

void UAFVitalAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFVitalAttributeSet, Health, OldHealth);
}

void UAFVitalAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFVitalAttributeSet, MaxHealth, OldMaxHealth);
}

void UAFVitalAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFVitalAttributeSet, Mana, OldMana);
}

void UAFVitalAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFVitalAttributeSet, MaxMana, OldMaxMana);
}

void UAFVitalAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFVitalAttributeSet, Stamina, OldStamina);
}

void UAFVitalAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAFVitalAttributeSet, MaxStamina, OldMaxStamina);
}

void UAFVitalAttributeSet::RecalculateVitalAttributes(const UAFPrimaryAttributeSet* PrimaryAS)
{
	const float Vit  = PrimaryAS->GetVitality();
	const float Int_ = PrimaryAS->GetIntelligence();
	const float Str  = PrimaryAS->GetStrength();

	const float NewMaxHealth  = Vit  * 10.0f;
	const float NewMaxMana    = Int_ * 8.0f;
	const float NewMaxStamina = Vit  * 3.0f + Str * 2.0f;

	SetMaxHealth (NewMaxHealth);
	SetMaxMana   (NewMaxMana);
	SetMaxStamina(NewMaxStamina);

	// 현재 값도 Max에 맞게 클램프
	SetHealth  (FMath::Clamp(GetHealth(),   0.f, NewMaxHealth));
	SetMana    (FMath::Clamp(GetMana(),     0.f, NewMaxMana));
	SetStamina (FMath::Clamp(GetStamina(),  0.f, NewMaxStamina));

	PRINTLOG(TEXT("[Vital]   MaxHealth=%.1f  MaxMana=%.1f  MaxStamina=%.1f"),
		GetMaxHealth(), GetMaxMana(), GetMaxStamina());
}
