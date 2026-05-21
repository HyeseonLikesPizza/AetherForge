
#include "AetherForge/Public/Player/AFPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attributes/AFVitalAttributeSet.h"
#include "GAS/Attributes/AFPrimaryAttributeSet.h"
#include "GAS/Attributes/AFDerivedAttributeSet.h"


AAFPlayerState::AAFPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	VitalAS   = CreateDefaultSubobject<UAFVitalAttributeSet>(TEXT("VitalAttributeSet"));
	PrimaryAS = CreateDefaultSubobject<UAFPrimaryAttributeSet>(TEXT("PrimaryAttributeSet"));
	DerivedAS = CreateDefaultSubobject<UAFDerivedAttributeSet>(TEXT("DerivedAttributeSet"));
}

UAbilitySystemComponent* AAFPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
