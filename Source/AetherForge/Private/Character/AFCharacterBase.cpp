

#include "AetherForge/Public/Character/AFCharacterBase.h"


AAFCharacterBase::AAFCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AAFCharacterBase::GetAbilitySystemComponent() const
{
	// TODO: ASC 리턴하기
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
