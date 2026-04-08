

#include "AetherForge/Public/Character/AFCharacterBase.h"

#include "Player/AFPlayerState.h"


AAFCharacterBase::AAFCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AAFCharacterBase::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AAFCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void AAFCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAFCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
