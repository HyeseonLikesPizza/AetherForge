
#include "AetherForge/Public/Player/AFPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"



void AAFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AAFPlayerController::OnSetDestinationStarted);
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
