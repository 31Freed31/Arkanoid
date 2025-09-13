// Freed31

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusParent.h"
#include "BonusTurnedCamera.generated.h"

UCLASS()
class ARKANOID_API ABonusTurnedCamera : public ABonusParent
{
	GENERATED_BODY()

public:
	virtual void BonusAction(APaddle* Paddle) override;

private:
	FRotator OriginalRotation;
	FTimerHandle TimerHandle_ResetCamera;
	bool bCameraTurned = false;

	void ResetCamera();
};
