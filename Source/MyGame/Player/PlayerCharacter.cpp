// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Makes the camera component and names it
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	// Assigns the camera to the root component (Player)
	Camera->SetupAttachment(RootComponent);

	// Sword setup
	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
	SwordMesh->SetupAttachment(GetMesh(), FName("SwordSocket"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Disable character's movement component rotation handling
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false; // Disable controller yaw control for custom rotations

	GetMesh()->PlayAnimation(IdleAnimation, true);
}

// Called every frame
// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the player is moving by checking velocity
	if (GetVelocity().Size() > 0.0f && bisAttacking == false) {
		if (!bisMoving) {  // If the player has started moving
			bisMoving = true;
			// Play the walking animation
			GetMesh()->PlayAnimation(WalkAnimation, true);
		}
	}
	else if (bisMoving && bisAttacking == false) {
		bisMoving = false;
		// If the player stops moving, play idle animation
		GetMesh()->PlayAnimation(IdleAnimation, true);
	}

	// Ensure walking animation plays if player is moving during attack
	if (bisAttacking == false && GetVelocity().Size() > 0.0f && !bisMoving) {
		// If still moving but not attacking, play walking animation
		bisMoving = true;
		GetMesh()->PlayAnimation(WalkAnimation, true);
	}

}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveBackward", this, &APlayerCharacter::MoveBackward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveLeft", this, &APlayerCharacter::MoveLeft);

	// Attack actions
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::StartAttack);
	PlayerInputComponent->BindAction("AttackAbility1", IE_Pressed, this, &APlayerCharacter::StartAttackAbility1);
	PlayerInputComponent->BindAction("AttackAbility2", IE_Pressed, this, &APlayerCharacter::StartAttackAbility2);
	PlayerInputComponent->BindAction("AttackAbility3", IE_Pressed, this, &APlayerCharacter::StartAttackAbility3);
	PlayerInputComponent->BindAction("AttackAbility4", IE_Pressed, this, &APlayerCharacter::StartAttackAbility4);
	PlayerInputComponent->BindAction("AttackAuraAbility", IE_Pressed, this, &APlayerCharacter::StartAttackAuraAbility);
}

void APlayerCharacter::MoveForward(float InputValue) {

	if (bisAttacking) {
		return;
	}

	// Move forward
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);

	// Update rotation to make the player face the movement direction
	if (InputValue != 0.f) {
		FRotator NewRotation = FRotator(0.f, GetActorRotation().Yaw, 0.f); // Retain current pitch and roll
		SetActorRotation(NewRotation); // Update actor rotation (capsule)

		// Sync mesh rotation with actor (capsule)
		GetMesh()->SetWorldRotation(FRotator(0.f, NewRotation.Yaw - 90.f, 0.f)); // Make sure the mesh faces the same way
	}
}

void APlayerCharacter::MoveBackward(float InputValue) {

	if (bisAttacking) {
		return;
	}

	// Move backward
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);  // Forward movement calculation

	// Update rotation to make the player face the movement direction
	if (InputValue != 0.f) {
		FRotator NewRotation = FRotator(0.f, GetActorRotation().Yaw, 0.f); // Retain current pitch and roll
		SetActorRotation(NewRotation); // Update actor rotation (capsule)

		// Sync mesh rotation with actor (capsule)
		GetMesh()->SetWorldRotation(FRotator(0.f, NewRotation.Yaw - -90.f, 0.f)); // Make sure the mesh faces the same way
	}
}

void APlayerCharacter::MoveRight(float InputValue) {

	if (bisAttacking) {
		return;
	}

	// Move right
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputValue);

	// Update rotation to make the player face the movement direction
	if (InputValue != 0.f) {
		FRotator NewRotation = FRotator(0.f, GetActorRotation().Yaw, 0.f); // Retain current pitch and roll
		SetActorRotation(NewRotation); // Update actor rotation (capsule)

		// Sync mesh rotation with actor (capsule)
		GetMesh()->SetWorldRotation(FRotator(0.f, NewRotation.Yaw, 0.f)); // Make sure the mesh faces the same way
	}
}

void APlayerCharacter::MoveLeft(float InputValue) {

	if (bisAttacking) {
		return;
	}

	// Move left
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputValue); // Use right direction vector for left movement

	// Update rotation to make the player face the movement direction
	if (InputValue != 0.f) {
		FRotator NewRotation = FRotator(0.f, GetActorRotation().Yaw, 0.f); // Retain current pitch and roll
		SetActorRotation(NewRotation); // Update actor rotation (capsule)

		// Sync mesh rotation with actor (capsule)
		GetMesh()->SetWorldRotation(FRotator(0.f, NewRotation.Yaw - 180.f, 0.f)); // Make sure the mesh faces the same way
	}
}

// Basic attack function
void APlayerCharacter::StartAttack() {
	bisMoving = false;
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
	// Get socket location for line trace
	FVector StartLocation = SwordMesh->GetSocketLocation(FName("Start"));
	FVector EndLocation = SwordMesh->GetSocketLocation(FName("End"));

	// Set up line trace
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	// Perform the line trace
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);

	// Draw debug line
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 1, 0, 1);
	if (HitResult.bBlockingHit) {
		AActor* ActorHit = HitResult.GetActor();
		ActorHit->Destroy();
	}
}

void APlayerCharacter::HandleEndAttackNotify() {
	bisAttacking = false;


}
