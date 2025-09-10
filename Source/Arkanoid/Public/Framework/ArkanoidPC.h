// Freed31

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArkanoidPC.generated.h"

UCLASS()
class ARKANOID_API AArkanoidPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	void ExitButtonPressed();
	void ShowGameEndMenu(const bool bWinStatus);
};
