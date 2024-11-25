#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VRGesturesComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVRGestures, Warning, All);

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
	float NodYesPitchThreshold = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Gestures|Nod Yes")
	float NodYesTimeThreshold = 0.5f;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* VRCamera;
	
protected:
	virtual void BeginPlay() override;

private:
	void CheckForNodYes(float DeltaTime, const FRotator& CurrentRotation);

	FRotator PreviousRotation;
};
