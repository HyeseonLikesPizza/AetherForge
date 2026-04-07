// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AFPlayerCharacter.h"


// Sets default values
AAFPlayerCharacter::AAFPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAFPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAFPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

