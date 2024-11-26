#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VRGesturesComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVRGestures, All, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNodYes);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGESTURES_API UVRGesturesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVRGesturesComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Gestures|Nod Yes")
	bool bNodYesEnabled = true;

	UPROPERTY(EditAnywhere, Category = "Gestures|Nod Yes")
	float NodYesPitchThreshold = -3.0f;

	UPROPERTY(EditAnywhere, Category = "Gestures|Nod Yes")
	float NodYesCooldownTime = 0.5f;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* VRCamera;

	UPROPERTY(BlueprintAssignable)
	FOnNodYes OnNodYes;
	
protected:
	virtual void BeginPlay() override;

private:
	void CheckForNodYes(float DeltaTime, const FRotator& CurrentRotation);

	void ResetGestureState(bool& bGestureActive, float& GestureTime);
	
	FRotator PreviousRotation;

	// Move into struct
	bool bIsNodding = false;
	float NodYesTime = 0.0f;
};
