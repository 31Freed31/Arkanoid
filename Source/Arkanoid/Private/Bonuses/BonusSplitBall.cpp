// Freed31


#include "Bonuses/BonusSplitBall.h"
#include "Framework/Paddle.h"
#include "World/Ball.h"
#include "EngineUtils.h"
#include <Bonuses/BonusDestroyCubes.h>

ABonusSplitBall::ABonusSplitBall()
{

}

void ABonusSplitBall::BonusAction(APaddle* Paddle)
{
    TArray<ABall*> BallsToSplit;
    for (TActorIterator<ABall> It(GetWorld()); It; ++It)
    {
        if (ABall* Ball = *It)
        {
            BallsToSplit.Add(Ball);
        }
    }

    for (ABall* Ball : BallsToSplit)
    {
        Ball->SplitBall();
    }

    Super::BonusAction(Paddle);
}