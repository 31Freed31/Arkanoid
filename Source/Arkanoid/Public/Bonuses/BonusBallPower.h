// Freed31

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusParent.h"
#include "BonusBallPower.generated.h"


UCLASS()
class ARKANOID_API ABonusBallPower : public ABonusParent
{
	GENERATED_BODY()
	
public:
	ABonusBallPower();

protected:
	virtual void BonusAction(APaddle* Paddle) override;
};
