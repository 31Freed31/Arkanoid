// Freed31


#include "Framework/ArkanoidGameMode.h"
#include "Framework/ArkanoidGameState.h"
#include "Framework/ArkanoidPlayerState.h"
#include <Framework/ArkanoidPC.h>
#include "EngineUtils.h"
#include "World/PlayingBoard.h"

AArkanoidGameMode::AArkanoidGameMode()
{
	GameStateClass = AArkanoidGameState::StaticClass();
	PlayerStateClass = AArkanoidPlayerState::StaticClass();
}

void AArkanoidGameMode::BeginPlay()
{
	Super::BeginPlay();

	CalculatePlayingBoard();
	GameStarted();
	
}

void AArkanoidGameMode::CalculatePlayingBoard()
{
	for (TActorIterator<APlayingBoard> It(GetWorld()); It; ++It)
	{
		if (const auto CurrentBoard = *It)
			AmountPlayingBoard++;
	}
}

void AArkanoidGameMode::GameStarted()
{
	auto ArkanoidGameState = Cast<AArkanoidGameState>(GameState);
	if (ArkanoidGameState)
		ArkanoidGameState->StartGame();
}

void AArkanoidGameMode::GameEnded(const bool bIsWinner)
{
	AmountPlayingBoard = bIsWinner ? --AmountPlayingBoard : 0;

	if (!AmountPlayingBoard)
	{
		const auto ArkanoidGameState = Cast<AArkanoidGameState>(GameState);
		if (ArkanoidGameState)
			ArkanoidGameState->StopGame();

		//UE_LOG(LogTemp, Warning, TEXT("Game Ended"));

		for (APlayerState* PlayerState : GameState->PlayerArray)
		{
			if (PlayerState)
			{
				const auto Player = Cast<AArkanoidPC>(PlayerState->GetPlayerController());

				if (Player)
				{
					Player->ShowGameEndMenu(bIsWinner);
				}
			}

		}
	}

	
}
