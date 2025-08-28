// Freed31

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UArrowComponent;

UENUM(BlueprintType)
enum class EState : uint8
{
	Idle,
	Moving,
};

USTRUCT(BlueprintType)
struct FInitParameters
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Tooltip = "Start size"))
	float Scale;
	UPROPERTY(EditDefaultsOnly, meta = (Tooltip = "Start power"))
	int32 Power;
	UPROPERTY(EditDefaultsOnly, meta = (Tooltip = "Start speed"))
	float Speed;
	UPROPERTY(EditDefaultsOnly, meta = (Tooltip = "Start maximum speed"))
	float MaxSpeed;

	FInitParameters()
	{
		Scale = 1.0f;
		Power = 1;
		Speed = 500.0f;
		MaxSpeed = 2500.0f;
	}
};

UCLASS()
class ARKANOID_API ABall : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardArrow = nullptr;

	int32 Power = 1;
	float Speed = 0.0f;
	FVector Direction = FVector::ZeroVector;
	EState State = EState::Idle;

public:
	ABall();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	FInitParameters InitParameters;

	//Function for moving
	UFUNCTION(BlueprintCallable, Category = Ball)
	void Move(const float DeltaTime);

	void SetBallState(const EState NewState);

};
