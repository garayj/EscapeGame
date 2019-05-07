// Copyright Ben Tristem 2016.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()
protected:

public:	
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets default values for this component's properties
	UOpenDoor();

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

	void CloseDoor();

private:
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate = nullptr; 

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;

	AActor *Owner = nullptr;

	///Returns total mass on the plate in kg
	float GetTotalMassOfActorOnPlate();
}; 