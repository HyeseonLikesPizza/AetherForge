
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AFForgerComponent.generated.h"

class UAbilitySystemComponent;
class UAFAbilitySet;
class UInputAction;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AETHERFORGE_API UAFForgerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAFForgerComponent();

	// 입력 바인딩 초기화
	void InitializePlayerInput(UInputComponent* InputComponent);

	// 어빌리티 활성화
	void TryActivateAbilityByInputTag(FGameplayTag InputTag);

	void GiveAbilities(UAbilitySystemComponent* ASC);

	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Ability")
	TObjectPtr<UAFAbilitySet> AbilitySet;

	UPROPERTY(EditAnywhere, Category = "Input")
	TMap<TObjectPtr<UInputAction>, FGameplayTag> InputTagMap;
};
