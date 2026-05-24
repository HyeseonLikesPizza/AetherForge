
#pragma once

#include "CoreMinimal.h"
#include "AFCharacterBase.h"
#include "AFPlayerCharacter.generated.h"

class UAFForgerComponent;
class UAFAbilitySet;
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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UAFForgerComponent* GetForgerComponent() const { return ForgerComponent; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> InitPrimaryAttributeGEClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> InitVitalAttributeGEClass;

private:
	UPROPERTY(VisibleAnywhere, Category = "Ability")
	TObjectPtr<UAFForgerComponent> ForgerComponent;
};
