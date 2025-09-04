// Freed31

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusParent.h"
#include "BonusPaddleSize.generated.h"

UCLASS()
class ARKANOID_API ABonusPaddleSize : public ABonusParent
{
	GENERATED_BODY()
	
public:	
	ABonusPaddleSize();

protected:

	virtual void BonusAction(APaddle* Paddle) override;
};
