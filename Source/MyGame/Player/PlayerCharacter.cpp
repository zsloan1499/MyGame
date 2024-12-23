// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Makes the camera coponent names it
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	//assigns the camera to the root component (Player)
	Camera->SetupAttachment(RootComponent);

	//if we wanted first person
	//Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//If we ever want to jump
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	//
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);

	//
	PlayerInputComponent->BindAxis("MoveBackward", this, &APlayerCharacter::MoveBackward);

	//
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	//
	PlayerInputComponent->BindAxis("MoveLeft", this, &APlayerCharacter::MoveLeft);




}

void APlayerCharacter::MoveForward(float InputValue) {

	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);

}

void APlayerCharacter::MoveBackward(float InputValue) {

	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);

}

void APlayerCharacter::MoveRight(float InputValue) {

	FVector RigthDirection = GetActorRightVector();
	AddMovementInput(RigthDirection, InputValue);

}

void APlayerCharacter::MoveLeft(float InputValue) {

	FVector RigthDirection = GetActorRightVector();
	AddMovementInput(RigthDirection, InputValue);

}

