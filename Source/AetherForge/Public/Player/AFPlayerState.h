
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AFPlayerState.generated.h"

class UAFVitalAttributeSet;
class UAFPrimaryAttributeSet;
class UAFDerivedAttributeSet;

UCLASS()
class AETHERFORGE_API AAFPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAFPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void InitializeDerivedAttributes();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAFVitalAttributeSet> VitalAS;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAFPrimaryAttributeSet> PrimaryAS;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAFDerivedAttributeSet> DerivedAS;
};
