// Freed31

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusParent.h"
#include "BonusSplitBall.generated.h"


UCLASS()
class ARKANOID_API ABonusSplitBall : public ABonusParent
{
	GENERATED_BODY()

public:
	ABonusSplitBall();
	
protected:

	virtual void BonusAction(APaddle* Paddle) override;
};
