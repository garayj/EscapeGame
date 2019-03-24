// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
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
	AActor * Owner = GetOwner();

	FRotator newRotate = FRotator(0.0, -60.0, 0.0);

	Owner->SetActorRotation(newRotate);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Poll the Trigger Volume
	//if the ActorTheOpens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}
	else {
		CloseDoor();
	}
}

void UOpenDoor::CloseDoor()
{
	AActor * Owner = GetOwner();

	FRotator newRotate = FRotator(0.0, 0.0, 0.0);

	Owner->SetActorRotation(newRotate);
}

