// Copyright Ben Tristem 2016.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 150.f;

	UPhysicsHandleComponent *PhysicsHandle = nullptr;

	UInputComponent *InputComponent = nullptr;


	// Returns the reach of the players arm to interact with objects.
	FVector CalculateLineTraceEnd();
	// Returns the players location.
	FVector CalculateLineTraceStart();

	// Ray-cast and grab what's in reach
	void Grab();
		
	// Ray-cast and release what's in your hands. 
	void Release();

	//Find attached physics component
	void FindPhysicsHandleComponent();

	//Find attached input component	
	void SetupInputComponent();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
};
