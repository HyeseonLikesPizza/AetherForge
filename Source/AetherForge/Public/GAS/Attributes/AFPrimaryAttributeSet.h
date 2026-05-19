#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AFPrimaryAttributeSet.generated.h"

#ifndef ATTRIBUTE_ACCESSORS
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
#endif

UCLASS()
class AETHERFORGE_API UAFPrimaryAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAFPrimaryAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// 물리 공격력, 방어력 일부에 기여
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Strength, Category="Attributes|Primary")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAFPrimaryAttributeSet, Strength)

	// 명중률, 치명타율, 공격속도에 기여
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Dexterity, Category="Attributes|Primary")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UAFPrimaryAttributeSet, Dexterity)

	// 마법 공격력, 최대 마나에 기여
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Intelligence, Category="Attributes|Primary")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAFPrimaryAttributeSet, Intelligence)

	// 최대 체력, 물리 방어력에 기여
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Vitality, Category="Attributes|Primary")
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UAFPrimaryAttributeSet, Vitality)

protected:
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	UFUNCTION()
	void OnRep_Vitality(const FGameplayAttributeData& OldVitality);
};
