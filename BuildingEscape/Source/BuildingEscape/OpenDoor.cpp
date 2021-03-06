// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

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
	Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Poll the Trigger Volume
	//if the ActorTheOpens is in the volume

	if (GetTotalMassOfActorOnPlate() > TriggerMass) {
		OnOpen.Broadcast();
	}
	else{
		OnClose.Broadcast();
	}
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0, 0.0, 0.0));
}

float UOpenDoor::GetTotalMassOfActorOnPlate()
{
	
	float TotalMass = 0.f;

	//Find all the overlapping actors
	if (PressurePlate == nullptr) { return TotalMass; }
	TArray<AActor*> OverlappingActors ;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto *actor : OverlappingActors) {
	//Iterate through them adding their masses

		TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

