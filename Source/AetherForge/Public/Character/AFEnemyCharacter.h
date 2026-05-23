
#pragma once

#include "CoreMinimal.h"
#include "AFCharacterBase.h"
#include "AFEnemyCharacter.generated.h"

UCLASS()
class AETHERFORGE_API AAFEnemyCharacter : public AAFCharacterBase
{
	GENERATED_BODY()

public:
	AAFEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
