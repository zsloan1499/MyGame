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
	SwordMesh->SetupAttachment(GetMesh(), FName("SwordSocket"));

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

	//Move forward
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);

	//move backward
	PlayerInputComponent->BindAxis("MoveBackward", this, &APlayerCharacter::MoveBackward);

	//move right
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	//move left
	PlayerInputComponent->BindAxis("MoveLeft", this, &APlayerCharacter::MoveLeft);
	
	//Attack
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::StartAttack);




}

void APlayerCharacter::MoveForward(float InputValue) {

	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);
	GetMesh()->PlayAnimation(WalkAnimation, true);

}

void APlayerCharacter::MoveBackward(float InputValue) {

	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);
	GetMesh()->PlayAnimation(WalkAnimation, true);

}

void APlayerCharacter::MoveRight(float InputValue) {

	FVector RigthDirection = GetActorRightVector();
	AddMovementInput(RigthDirection, InputValue);
	GetMesh()->PlayAnimation(WalkAnimation, true);
//checking something
}

void APlayerCharacter::MoveLeft(float InputValue) {

	FVector RigthDirection = GetActorRightVector();
	AddMovementInput(RigthDirection, InputValue);
	GetMesh()->PlayAnimation(WalkAnimation , true);

}

void APlayerCharacter::Block() {
	
	bisBlocking = true;
	GetMesh()->PlayAnimation(BlockAnimation, false);

}

void APlayerCharacter::StartAttack() {

	//call attack animation
	if (BasicAttackAnimation && bisAttacking == false) {

		GetMesh()->PlayAnimation(BasicAttackAnimation, false);
		bisAttacking = true;
	}

}

// for weapon during an attack
void APlayerCharacter::LineTrace() {


	//Get Socket locations of the Sword, Start and end
	FVector StartLocation = SwordMesh->GetSocketLocation(FName("Start"));
	FVector EndLocation = SwordMesh->GetSocketLocation(FName("End"));


	//Setup Line Trace
	//object we hit with sword
	FHitResult HitResult;

	FCollisionQueryParams TraceParams;

	//dont hit ourselves
	TraceParams.AddIgnoredActor(this);

	//Linetrace
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);

	//draw debig lines
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 1, 0, 1);

	if (HitResult.bBlockingHit) {

		AActor* ActorHit = HitResult.GetActor();
		ActorHit->Destroy();

	}



	//Line trace



}

