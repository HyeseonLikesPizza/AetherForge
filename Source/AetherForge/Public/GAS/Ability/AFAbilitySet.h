
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Engine/DataAsset.h"
#include "AFAbilitySet.generated.h"
class UAbilitySystemComponent;
class UAFGameplayAbility;

USTRUCT(BlueprintType)
struct FAFAbilitySet_GameplayAbility
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAFGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere)
	FGameplayTag InputTag; 
};

UCLASS()
class AETHERFORGE_API UAFAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:
	// 어빌리티 부여
	void GiveAbilities(UAbilitySystemComponent* ASC);

	// 어빌리티 회수
	void TakeAbilities(UAbilitySystemComponent* ASC);

	// 어빌리티 실행
	void TryActivateAbilityByInputTag(UAbilitySystemComponent* ASC, FGameplayTag InputTag);

protected:
	UPROPERTY(EditAnywhere)
	TArray<FAFAbilitySet_GameplayAbility> GrantedAbilities;

private:
	UPROPERTY()
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> InputTagToHandle;
};
