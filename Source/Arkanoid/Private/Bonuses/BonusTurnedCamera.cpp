#include "Bonuses/BonusTurnedCamera.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void ABonusTurnedCamera::BonusAction(APaddle* Paddle)
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC) return;

    AActor* ViewTarget = PC->GetViewTarget();
    if (!ViewTarget) return;

    // Сохраняем rotation только если камера ещё не перевёрнута
    if (!bCameraTurned)
    {
        OriginalRotation = ViewTarget->GetActorRotation();
        bCameraTurned = true;
    }

    // Переворачиваем по Roll
    FRotator NewRotation = OriginalRotation;
    NewRotation.Roll += 180.0f;
    ViewTarget->SetActorRotation(NewRotation);

    // Сбросить предыдущий таймер, если он был
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ResetCamera);

    // Установить новый таймер на 5 секунд
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_ResetCamera, this, &ABonusTurnedCamera::ResetCamera, 5.0f, false);
}

void ABonusTurnedCamera::ResetCamera()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC) return;

    AActor* ViewTarget = PC->GetViewTarget();
    if (!ViewTarget) return;

    ViewTarget->SetActorRotation(OriginalRotation);
    bCameraTurned = false;
}
