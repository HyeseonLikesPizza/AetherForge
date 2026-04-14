#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "AFAnimInstance.generated.h"

class UCharacterMovementComponent;

UCLASS()
class AETHERFORGE_API UAFAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation|Movement")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Animation|Movement")
	bool bIsMoving;

	UPROPERTY(BlueprintReadOnly, Category = "Animation|Movement")
	bool bIsFalling;
	
	UPROPERTY(BlueprintReadOnly, Category = "Animation|GAS")
	FGameplayTagContainer OwnedGameplayTags;

private:
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CachedMovementComponent;
};
