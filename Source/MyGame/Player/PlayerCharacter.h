// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MYGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	//class and * mean it is a component
	//makes the camera component
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	//set up the walking animation
	UPROPERTY(EditAnywhere)
	class UAnimSequence* WalkAnimation;

	//set up the sword mesh
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* SwordMesh;

	//set up the shield mesh
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ShieldMesh;

	//Basic Attack animation, common attack
	UPROPERTY(EditAnywhere)
	class UAnimSequence* BasicAttackAnimation;

	//Ability 1 animation
	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAnimationOption1;

	//Ability 2 animation
	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAnimationOption2;

	//Ability 3 Animation
	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAnimationOption3;

	//Ability 4 Animation
	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAnimationOption4;

	//Ability 5 Animation
	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAnimationOption5;

	//Block animation
	UPROPERTY(EditAnywhere)
	class UAnimSequence* BlockAnimation;


	void MoveForward(float InputValue);
	void MoveBackward(float InputValue);
	void MoveRight(float InputValue);
	void MoveLeft(float InputValue);

	//attack
	int Damage;

	void StartAttack();

	void Block();


public:

	UFUNCTION(BlueprintCallable)
	void LineTrace();

	UPROPERTY(BlueprintReadWrite)
	bool bisAttacking;

	UPROPERTY(BlueprintReadWrite)
	bool bisBlocking;
};
