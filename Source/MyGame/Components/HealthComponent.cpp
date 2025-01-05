#include "MyGame/Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	bCanTakeDamage = true;

	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UHealthComponent::Die()
{

	GetOwner()->Destroy();

}


void UHealthComponent::TakeDamage(int Damage)
{
	if (bCanTakeDamage) {

		Health -= Damage;
		bCanTakeDamage = false;
		FTimerHandle InvincibilityDelay;
		GetWorld()->GetTimerManager().SetTimer(InvincibilityDelay, this, &UHealthComponent::AllowTakeDamage, 0.5f, false);

		if (Health <= 0) {
			Die();
		}
	}




}

void UHealthComponent::AllowTakeDamage()
{

	bCanTakeDamage = true;

}

