// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();	
}

void UOpenDoor::OpenDoor()
{
	// Find the owning actor
	FString ObjectName = GetOwner()->GetName();
	// Create a rotations
	FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
	// Set the door rotation
	GetOwner()->SetActorRotation(Rotation);
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll trigger volume every frame
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) 
	{
		// If ActorThatOpens is in volume
		OpenDoor();
	}
}

