
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AFPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class AETHERFORGE_API AAFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

protected:
	// Enhanced Input
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LMBAction;

private:
	void OnLMBPressed();
	void OnSetDestinationStarted();
	
	// 내부 상태
	FVector CachedDestination;
};
