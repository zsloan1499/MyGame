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

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* SwordMesh;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* WalkAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* IdleAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAbility1Animation;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAbility2Animation;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAbility3Animation;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAbility4Animation;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAuraAbilityAnimation;

	UPROPERTY(BlueprintReadWrite)
	bool bisMoving;  // This tracks whether the player is moving








	void MoveForward(float InputValue);
	void MoveBackward(float InputValue);
	void MoveRight(float InputValue);
	void MoveLeft(float InputValue);

	int Damage();

	void StartAttack();

	void StartAttackAbility1();
	void StartAttackAbility2();
	void StartAttackAbility3();
	void StartAttackAbility4();
	void StartAttackAuraAbility();

	FVector StartPosition;


public:

	UPROPERTY(BlueprintReadWrite)
	bool bisAttacking;

	UFUNCTION(BlueprintCallable)
	void LineTrace();

	UFUNCTION(BlueprintCallable)
	void HandleEndAttackNotify();

};