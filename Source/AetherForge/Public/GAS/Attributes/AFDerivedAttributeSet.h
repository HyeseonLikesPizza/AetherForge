#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attributes/AFPrimaryAttributeSet.h"
#include "AFDerivedAttributeSet.generated.h"

#ifndef ATTRIBUTE_ACCESSORS
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
#endif

UCLASS()
class AETHERFORGE_API UAFDerivedAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAFDerivedAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void RecalculateDerivedAttributes(const UAFPrimaryAttributeSet* PrimaryAS);

	// Strength * 2 → 물리 스킬 데미지 계산에 사용
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AttackPower, Category="Attributes|Derived")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UAFDerivedAttributeSet, AttackPower)

	// Intelligence * 2 → 마법 스킬 데미지 계산에 사용
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MagicPower, Category="Attributes|Derived")
	FGameplayAttributeData MagicPower;
	ATTRIBUTE_ACCESSORS(UAFDerivedAttributeSet, MagicPower)

	// Vitality * 1.5 + Strength * 0.5 → 받는 물리 데미지 감소
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Defense, Category="Attributes|Derived")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UAFDerivedAttributeSet, Defense)

	// Dexterity * 1.0 → 적중 판정에 사용
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HitRate, Category="Attributes|Derived")
	FGameplayAttributeData HitRate;
	ATTRIBUTE_ACCESSORS(UAFDerivedAttributeSet, HitRate)

	// Dexterity * 0.3 → 치명타 확률 (%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CritRate, Category="Attributes|Derived")
	FGameplayAttributeData CritRate;
	ATTRIBUTE_ACCESSORS(UAFDerivedAttributeSet, CritRate)

protected:
	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);

	UFUNCTION()
	void OnRep_MagicPower(const FGameplayAttributeData& OldMagicPower);

	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldDefense);

	UFUNCTION()
	void OnRep_HitRate(const FGameplayAttributeData& OldHitRate);

	UFUNCTION()
	void OnRep_CritRate(const FGameplayAttributeData& OldCritRate);
};
