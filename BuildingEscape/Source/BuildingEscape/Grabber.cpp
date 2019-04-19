// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerLocation, 
		PlayerRotation);
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;

	// If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		//move the object that we're holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

 }


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}
///Look for attached Physics Component
void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		//found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component."), *GetOwner()->GetName());
	}
}

///Look for attached Input Component (only appears at runtime)
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	///Look for attached InputComponent (only appears at run time)
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has input component."), *GetOwner()->GetName());
		///Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerLocation, 
		PlayerRotation);
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;

	///Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	///Line-trace (AKA ray-cast) put to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor *AActorHit = Hit.GetActor();
	if (AActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *AActorHit->GetName());
	}
	return Hit;
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed."), *GetOwner()->GetName());

	///LINE TRACE and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();

	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	
	///If we hit something then attach a physics handle
	if (ActorHit) {
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true //Allow rotation
		);
	}

}


void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Released!"), *GetOwner()->GetName());
	//TODO release physics handle
	PhysicsHandle->ReleaseComponent();
}

