
#include "Character/AFPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Player/AFPlayerState.h"


AAFPlayerCharacter::AAFPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AAFPlayerCharacter::GetAbilitySystemComponent() const
{
	AAFPlayerState* PS = GetPlayerState<AAFPlayerState>();
	return PS ? PS->GetAbilitySystemComponent() : nullptr;
}

void AAFPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// ASC 설정 - 서버 측에서 실행
	// 이 시점에서 PlayerState와 Character 모두 유효함
	if (AAFPlayerState* PS = GetPlayerState<AAFPlayerState>())
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}
}

void AAFPlayerCharacter::OnRep_PlayerState()
{
	// ASC 설정 - 클라 측에서 실행
	// 이 시점에서 PlayerState와 Character 모두 유효함
	if (AAFPlayerState* PS = GetPlayerState<AAFPlayerState>())
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}
}

void AAFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

