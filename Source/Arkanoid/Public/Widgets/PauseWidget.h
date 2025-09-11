// Freed31

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameResume);

class UTextBlock;
class UButton;
class USoundBase;

UCLASS()
class ARKANOID_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess=true))
	UTextBlock* StatusText = nullptr;
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UButton* ResumeButton = nullptr;
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UButton* RestartButton = nullptr;
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UButton* MenuButton = nullptr;

protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void ResumeGame();
	UFUNCTION()
	void RestartGame();
	UFUNCTION()
	void BackToMenu();

public:

	UPROPERTY(BlueprintAssignable, Category = "PauseWidget")
	FOnGameResume OnGameResume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere , Category = "PauseWidget")
	USoundBase* WinSound = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PauseWidget")
	USoundBase* LooseSound = nullptr;


	void SetWinStatus(const bool bWinStatus);
};
