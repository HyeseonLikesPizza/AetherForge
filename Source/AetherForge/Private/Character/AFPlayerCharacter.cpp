
#include "Character/AFPlayerCharacter.h"
#include "AetherForge.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AFPlayerState.h"
#include "AetherForge/Public/Character/AFAnimInstance.h"


AAFPlayerCharacter::AAFPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// 캡슐 컴포넌트를 루트 컴포넌트로 설정
	SetRootComponent(GetCapsuleComponent());

	// 캡슐에 메시 붙이기
	GetMesh()->SetupAttachment(GetRootComponent());

	// 메시 위치/회전 (Z=-90: 캡슐 중심→발바닥, Yaw=-90: DCC +Y전방→UE5 +X전방)
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -90.f),
		FRotator(0.f, -90.f, 0.f)
	);

	// AnimClass 지정 (블루프린트 ABP에서 오버라이드 가능)
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(UAFAnimInstance::StaticClass());

	// 스프링암과 카메라 생성
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// 스프링암에 카메라 부착
	Camera->SetupAttachment(SpringArm);

	// 캡슐에 스프링암 부착
	SpringArm->SetupAttachment(GetRootComponent());

	// 탑다운 카메라 고정 (캐릭터/컨트롤러 회전 무시)
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	// 이동 방향으로 캐릭터 회전 (클릭 투 무브용)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->bOrientRotationToMovement = true;
		Movement->RotationRate = FRotator(0.f, 540.f, 0.f);
	}
}

UAbilitySystemComponent* AAFPlayerCharacter::GetAbilitySystemComponent() const
{
	AAFPlayerState* PS = GetPlayerState<AAFPlayerState>();
	return PS ? PS->GetAbilitySystemComponent() : nullptr;
}

void AAFPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// ASC 설정 - 서버 측에서 실행
	// 이 시점에서 PlayerState와 Character 모두 유효함
	if (AAFPlayerState* PS = GetPlayerState<AAFPlayerState>())
	{
		if (UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
		{
			ASC->InitAbilityActorInfo(PS, this);

			// GE_InitPrimaryAttribute 설정
			if (InitPrimaryAttributeGEClass)
			{
				FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
				FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
					InitPrimaryAttributeGEClass, 1.0f, ContextHandle);

				if (SpecHandle.IsValid())
				{
					ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
					PRINTLOG(TEXT("GE_InitPrimaryAttributes applied: %s"), *InitPrimaryAttributeGEClass->GetName());
				}
				else
				{
					PRINTLOG(TEXT("GE_InitPrimaryAttributes SpecHandle invalid: %s"), *InitPrimaryAttributeGEClass->GetName());
				}
			}
			else
			{
				PRINTLOG(TEXT("InitPrimaryAttributeGEClass is not set on %s"), *GetName());
			}

			// GE_InitVitalAttributes 설정
			if (InitVitalAttributeGEClass)
			{
				FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
				FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
					InitVitalAttributeGEClass, 1.0f, ContextHandle);

				if (SpecHandle.IsValid())
				{
					ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
					PRINTLOG(TEXT("GE_InitVitalAttributes applied: %s"), *InitVitalAttributeGEClass->GetName());
				}
				else
				{
					PRINTLOG(TEXT("GE_InitVitalAttributes SpecHandle invalid: %s"), *InitVitalAttributeGEClass->GetName());
				}
			}
			else
			{
				PRINTLOG(TEXT("InitVitalAttributeGEClass is not set on %s"), *GetName());
			}
		}

	}
}

void AAFPlayerCharacter::OnRep_PlayerState()
{
	// ASC 설정 - 클라 측에서 실행
	// 이 시점에서 PlayerState와 Character 모두 유효함
	if (AAFPlayerState* PS = GetPlayerState<AAFPlayerState>())
	{
		if (UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
		{
			ASC->InitAbilityActorInfo(PS, this);
		}

	}
}

void AAFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

