// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"




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
	
	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
	SwordMesh->SetupAttachment(GetMesh(),FName("SwordSocket"));
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

	//w
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);

	//s
	PlayerInputComponent->BindAxis("MoveBackward", this, &APlayerCharacter::MoveBackward);

	//d
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	//a
	PlayerInputComponent->BindAxis("MoveLeft", this, &APlayerCharacter::MoveLeft);

	//LMB
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::StartAttack);

	PlayerInputComponent->BindAction("AttackAbility1", IE_Pressed, this, &APlayerCharacter::StartAttackAbility1);

	PlayerInputComponent->BindAction("AttackAbility2", IE_Pressed, this, &APlayerCharacter::StartAttackAbility2);

	PlayerInputComponent->BindAction("AttackAbility3", IE_Pressed, this, &APlayerCharacter::StartAttackAbility3);

	PlayerInputComponent->BindAction("AttackAbility4", IE_Pressed, this, &APlayerCharacter::StartAttackAbility4);

	PlayerInputComponent->BindAction("AttackAuraAbility", IE_Pressed, this, &APlayerCharacter::StartAttackAuraAbility);


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
	//checking something
}

void APlayerCharacter::MoveLeft(float InputValue) {

	FVector RigthDirection = GetActorRightVector();
	AddMovementInput(RigthDirection, InputValue);

}

//basic attack
void APlayerCharacter::StartAttack() {

	if (AttackAnimation && !bisAttacking) {

		GetMesh()->PlayAnimation(AttackAnimation, false);
		bisAttacking = true;

	}




}

void APlayerCharacter::StartAttackAbility1() {

	if (AttackAbility1Animation) {

		GetMesh()->PlayAnimation(AttackAbility1Animation, false);
		bisAttacking = true;

	}




}

void APlayerCharacter::StartAttackAbility2() {

	if (AttackAbility2Animation) {

		GetMesh()->PlayAnimation(AttackAbility2Animation, false);
		bisAttacking = true;

	}




}

void APlayerCharacter::StartAttackAbility3() {

	if (AttackAbility3Animation) {

		GetMesh()->PlayAnimation(AttackAbility3Animation, false);
		bisAttacking = true;

	}




}

void APlayerCharacter::StartAttackAbility4() {

	if (AttackAbility4Animation) {

		GetMesh()->PlayAnimation(AttackAbility4Animation, false);
		bisAttacking = true;

	}




}

void APlayerCharacter::StartAttackAuraAbility() {

	if (AttackAuraAbilityAnimation) {

		GetMesh()->PlayAnimation(AttackAuraAbilityAnimation, false);
		bisAttacking = true;

	}




}

void APlayerCharacter::LineTrace() {

	//get socket location
	FVector StartLocation = SwordMesh->GetSocketLocation(FName("Start"));
	FVector EndLocation = SwordMesh->GetSocketLocation(FName("End"));

	//set up linetrace
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	
	//linetrace
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);


	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 1, 0, 1);
	if (HitResult.bBlockingHit) {

		AActor* ActorHit = HitResult.GetActor();
		ActorHit->Destroy();

	}



}

