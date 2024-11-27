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

	// Ideally would look for a nod gesture in a certain time frame and also head moving down and up,
	// but for now this also works by just moving head down quickly (thus the check for pitch < -3.0f)
	// TODO: Needs check for a head up movement after head down movement to confirm nod gesture 
	float DeltaYaw = CurrentRotation.Pitch - PreviousRotation.Pitch;
	if (DeltaYaw < NodYesPitchThreshold && CurrentRotation.Pitch < -4.0f && !bIsNodding && DeltaYaw < 0.0f)
	{
		bIsNodding = true;
		OnNodYes.Broadcast();
	}
	else if (bIsNodding)
	{
		// Process Cooldown
		NodYesTime += DeltaTime;
		if (NodYesTime >= NodYesCooldownTime)
		{
			ResetGestureState(bIsNodding, NodYesTime);
		}
	}
}

void UVRGesturesComponent::ResetGestureState(bool& bGestureActive, float& GestureTime)
{
	bGestureActive = false;
	GestureTime = 0.0f;
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

