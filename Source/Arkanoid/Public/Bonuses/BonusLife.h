// Freed31

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusParent.h"
#include "BonusLife.generated.h"

UCLASS()
class ARKANOID_API ABonusLife : public ABonusParent
{
	GENERATED_BODY()
	
public:
	ABonusLife();

protected:

	virtual void BonusAction(APaddle* Paddle) override;
};
