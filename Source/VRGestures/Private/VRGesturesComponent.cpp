#include "VRGesturesComponent.h"

#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY(LogVRGestures);

UVRGesturesComponent::UVRGesturesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UVRGesturesComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UVRGesturesComponent::CheckForNodYes(float DeltaTime, const FRotator& CurrentRotation)
{
	if (!bNodYesEnabled)
	{
		UE_LOG(LogVRGestures, Warning, TEXT("Nod Yes is not enabled"));
		return;
	}

	FRotator DeltaRotation = CurrentRotation - PreviousRotation;

	UE_LOG(LogVRGestures, Warning, TEXT("Delta Rotation: %s"), *DeltaRotation.ToString());
}

void UVRGesturesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!VRCamera)
	{
		UE_LOG(LogVRGestures, Warning, TEXT("No VRCamera set for the Gesture Component"));
		return;
	}

	const FRotator CurrentRotation = VRCamera->GetComponentRotation();

	// Check for gestures
	CheckForNodYes(DeltaTime, CurrentRotation);

	PreviousRotation = CurrentRotation;
}

