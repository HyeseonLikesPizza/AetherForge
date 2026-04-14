
#include "AetherForge/Public/Player/AFPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attributes/AFAttributeSet.h"

AAFPlayerState::AAFPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AS = CreateDefaultSubobject<UAFAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AAFPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
