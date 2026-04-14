
#include "Character/AFPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AFPlayerState.h"


AAFPlayerCharacter::AAFPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// 캡슐 컴포넌트를 루트 컴포넌트로 설정
	SetRootComponent(GetCapsuleComponent());

	// 캡슐에 메시 붙이기
	GetMesh()->SetupAttachment(GetRootComponent());

	// 스프링암과 카메라 생성
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// 스프링암에 카메라 부착
	Camera->SetupAttachment(SpringArm);

	// 캡슐에 스프링암 부착
	SpringArm->SetupAttachment(GetRootComponent());
	
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
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}
}

void AAFPlayerCharacter::OnRep_PlayerState()
{
	// ASC 설정 - 클라 측에서 실행
	// 이 시점에서 PlayerState와 Character 모두 유효함
	if (AAFPlayerState* PS = GetPlayerState<AAFPlayerState>())
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}
}

void AAFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

