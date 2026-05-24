
#pragma once

#include "CoreMinimal.h"
#include "AFGameplayAbility.h"
#include "AFGameplayAbility_BasicAttack.generated.h"

class UAnimMontage;
class UGameplayEffect;

UCLASS()
class AETHERFORGE_API UAFGameplayAbility_BasicAttack : public UAFGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	UAnimMontage* AttackMontage;

	// 스윕 구체 반지름
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	float SweepRadius = 50.f;

	// 캐릭터 앞 얼마나 멀리까지 판정할지
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	float DamageRadius = 150.f;

private:

	UFUNCTION()
	void PerformSweepAttack(FGameplayEventData Payload);
};
