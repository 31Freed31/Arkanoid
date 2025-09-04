// Freed31


#include "Bonuses/BonusPaddleSize.h"
#include "Framework/Paddle.h"

ABonusPaddleSize::ABonusPaddleSize()
{
	Duration = 10.0f;
}

void ABonusPaddleSize::BonusAction(APaddle* Paddle)
{
	Paddle->BonusChangeSize(Value, Duration);

	Super::BonusAction(Paddle);
}
