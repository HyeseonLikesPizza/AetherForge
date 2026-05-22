
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AFGameplayAbility.generated.h"

class UAFPrimaryAttributeSet;
class UAFVitalAttributeSet;

UENUM(BlueprintType)
enum class EAFAbilityActivationPolicy : uint8
{
	OnInputTriggered, // 키 누를 때 발동
	OnGiven			  // 부여받는 즉시 발동 (패시브)
};

UCLASS()
class AETHERFORGE_API UAFGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// 이 어빌리티가 무엇인지 식별하는 Tag
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	FGameplayTag AbilityTag;

	// 활성화 정책
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EAFAbilityActivationPolicy ActivationPolicy;

	const UAFVitalAttributeSet* GetVitalAttributeSet() const;
	const UAFPrimaryAttributeSet* GetPrimaryAttributeSet() const;
	
};
