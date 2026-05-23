
#include "AetherForge/Public/Player/AFPlayerController.h"
#include "AetherForge.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/AFEnemyCharacter.h"
#include "Character/AFPlayerCharacter.h"
#include "GAS/AFGameplayTags.h"
#include "Player/AFForgerComponent.h"

void AAFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// 마우스 클릭 액션 추가
		EIC->BindAction(LMBAction, ETriggerEvent::Started, this, &AAFPlayerController::OnLMBPressed);
	}
}

void AAFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	bShowMouseCursor = true;
}

void AAFPlayerController::OnLMBPressed()
{
	PRINTINFO();

	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		PRINTLOG(TEXT("Hit Actor: %s"), Hit.GetActor() ? *Hit.GetActor()->GetName() : TEXT("None"));

		if (Hit.GetActor() && Cast<AAFEnemyCharacter>(Hit.GetActor()))
		{
			PRINTLOG(TEXT("Enemy detected, activating ability"));
			if (AAFPlayerCharacter* PlayerCharacter = Cast<AAFPlayerCharacter>(GetPawn()))
			{
				PlayerCharacter->GetForgerComponent()->TryActivateAbilityByInputTag(AFGameplayTags::Input_LMB);
			}
		}
		else
		{
			PRINTLOG(TEXT("Ground detected, moving"));
			OnSetDestinationStarted();
		}
	}
	else
	{
		PRINTLOG(TEXT("No hit result"));
	}
}

void AAFPlayerController::OnSetDestinationStarted()
{
	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		// NavMesh 이동 가능?
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (NavSys == nullptr) return;

		FNavLocation NavLocation;
		if (NavSys->ProjectPointToNavigation(Hit.Location, NavLocation))
		{
			// NavMesh 위에 있는 위치만 이동 처리
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NavLocation.Location);
		}
	}
}
