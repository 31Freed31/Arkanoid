// Freed31

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusParent.h"
#include "BonusDestroyCubes.generated.h"

UCLASS()
class ARKANOID_API ABonusDestroyCubes : public ABonusParent
{
	GENERATED_BODY()

public:
	ABonusDestroyCubes();

protected:	

	virtual void BonusAction(APaddle* Paddle) override;
	
};
