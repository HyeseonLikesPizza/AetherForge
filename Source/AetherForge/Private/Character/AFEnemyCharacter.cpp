
#include "Character/AFEnemyCharacter.h"

AAFEnemyCharacter::AAFEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAFEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAFEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAFEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

