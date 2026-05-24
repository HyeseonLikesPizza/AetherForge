
#include "GAS/Ability/AFGameplayAbility_BasicAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

void UAFGameplayAbility_BasicAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 몽타주 재생 태스크
	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, TEXT("AttackMontageTask"), AttackMontage);

	MontageTask->OnCompleted.AddDynamic(this, &UAFGameplayAbility_BasicAttack::K2_EndAbility);
	MontageTask->OnCancelled.AddDynamic(this, &UAFGameplayAbility_BasicAttack::K2_EndAbility);
	MontageTask->OnInterrupted.AddDynamic(this, &UAFGameplayAbility_BasicAttack::K2_EndAbility);
	MontageTask->ReadyForActivation();

	// 히트 판정 타이밍 대기 태스크
	UAbilityTask_WaitGameplayEvent* EventTask =
		UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this, FGameplayTag::RequestGameplayTag(TEXT("Event.Montage.Attack.Hit")));
	
	EventTask->EventReceived.AddDynamic(this, &UAFGameplayAbility_BasicAttack::PerformSweepAttack);
	EventTask->ReadyForActivation();
}

void UAFGameplayAbility_BasicAttack::PerformSweepAttack(FGameplayEventData Payload)
{
	// @TODO 작성
	
}
