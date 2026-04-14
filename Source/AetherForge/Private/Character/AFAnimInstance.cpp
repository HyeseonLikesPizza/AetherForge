#include "AetherForge/Public/Character/AFAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAFAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		if (ACharacter* OwningCharacter = Cast<ACharacter>(OwningPawn))
		{
			CachedMovementComponent = OwningCharacter->GetCharacterMovement();
		}
	}
}

void UAFAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CachedMovementComponent) return;

	GroundSpeed = CachedMovementComponent->Velocity.Size2D();
	bIsMoving   = GroundSpeed > 3.0f;
	bIsFalling  = CachedMovementComponent->IsFalling();

	// TODO: OwnedGameplayTags: 추후 ASC->GetOwnedGameplayTags(OwnedGameplayTags) 채울것
}
