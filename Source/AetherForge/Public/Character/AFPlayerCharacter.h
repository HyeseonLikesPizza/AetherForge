
#pragma once

#include "CoreMinimal.h"
#include "AFCharacterBase.h"
#include "AFPlayerCharacter.generated.h"

class UGameplayEffect;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AETHERFORGE_API AAFPlayerCharacter : public AAFCharacterBase
{
	GENERATED_BODY()

public:
	AAFPlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> InitPrimaryAttributeGEClass;
};
