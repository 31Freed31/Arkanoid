// Freed31

#include "Bonuses/BonusDestroyCubes.h"
#include "World/PlayingBoard.h"
#include "EngineUtils.h"

ABonusDestroyCubes::ABonusDestroyCubes()
{
	Value = 3.0f;
}

void ABonusDestroyCubes::BonusAction(APaddle* Paddle)
{
	for (TActorIterator<APlayingBoard> It(GetWorld()) ; It; ++It)
	{
		if (const auto CurrentBoard = *It)
		{
			CurrentBoard->BonusDestroyCubes(Value);
			return;
		}
	}

	Super::BonusAction(Paddle);
}
