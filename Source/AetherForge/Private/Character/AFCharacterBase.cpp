

#include "AetherForge/Public/Character/AFCharacterBase.h"

#include "Player/AFPlayerState.h"


AAFCharacterBase::AAFCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* AAFCharacterBase::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AAFCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
