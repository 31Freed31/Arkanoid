// Freed31


#include "World/PlayingBoard.h"
#include "Bonuses/BonusParent.h"
#include "World/Block.h"
#include "Kismet/KismetMathLibrary.h"

void APlayingBoard::CreatePreviewComponents()
{
	if (GridSizeX <= 0 || GridSizeY <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("The grid size must be positive"));
		return;
	}

	const float BlockWidth = BlockScale.X * 100.0f;
	const float BlockHeight = BlockScale.Y * 100.0f;
	const float BlockDepth = BlockScale.Z * 100.0f;

	const float TotalWidth = GridSizeX * BlockWidth +(GridSizeX - 1) * SpacingX;
	const float TotalHeight = GridSizeY * BlockHeight + (GridSizeY - 1) * SpacingY;

	const FVector CenterOffset = FVector((TotalWidth - BlockWidth) / 2, (TotalHeight - BlockHeight) / 2, 0.0f);

	const FTransform ActorTransform = GetActorTransform();

	for (int32 x = 0; x < GridSizeX; x++)
	{
		for (int32 y = 0; y < GridSizeY; y++)
		{
			if (PreviewMesh)
			{
				const float XOffset = x * (BlockWidth + SpacingX);
				const float YOffset = y * (BlockHeight + SpacingY);
				const FVector PrewievLocation = FVector(XOffset, YOffset, 0.0f) - CenterOffset;
				const FVector WorldPreviewLocation = ActorTransform.TransformPosition(PrewievLocation);

				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(this);

				const FVector BoxExtents = FVector(BlockWidth * 0.5f , BlockHeight * 0.5f , BlockDepth * 0.5f);

				const bool bIsBlocked = GetWorld()->OverlapAnyTestByChannel(
					WorldPreviewLocation,
					ActorTransform.GetRotation(),
					ECC_Visibility,
					FCollisionShape::MakeBox(BoxExtents),
					CollisionParams
					);

				if (bIsBlocked)
				{
					DrawDebugBox(GetWorld(), WorldPreviewLocation, BoxExtents, ActorTransform.GetRotation(),
						FColor::Red, false, 10.0f);
					continue;
				}
				else
				{
					UStaticMeshComponent* PreviewComponent = NewObject<UStaticMeshComponent>(this);
					PreviewComponent->SetStaticMesh(PreviewMesh);
					PreviewComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
					PreviewComponent->SetRelativeScale3D(BlockScale);
					PreviewComponent->SetRelativeLocation(PrewievLocation);
					PreviewComponent->RegisterComponent();
					PreviewComponents.Add(PreviewComponent);
				}
			}
		}
	}
}

void APlayingBoard::ClearPreviewComponents()
{
	for(UStaticMeshComponent* PreviewComponent : PreviewComponents)
	{
		if (PreviewComponent)
		{
			PreviewComponent->DestroyComponent();
		}
	}
	PreviewComponents.Empty();
}

void APlayingBoard::SpawnBlockActors()
{
	for (UStaticMeshComponent* PreviewComponent : PreviewComponents)
	{
		if (PreviewComponent)
		{
			const FTransform SpawnTransform = PreviewComponent->GetComponentTransform();
			if (auto CurrentBlock = GetWorld()->SpawnActor<ABlock>(BlockClassForSpawn, SpawnTransform))
			{
				const int32 Life = UKismetMathLibrary::RandomBoolWithWeight(GameDifficulty) ? 2 : 1;

				const auto BonusClass = UKismetMathLibrary::RandomBoolWithWeight(BonusChance) ? GetBonusClass() : nullptr;

				CurrentBlock->Init(BlockScale, Life, BonusClass);

				CurrentBlock->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepWorldTransform);
				CurrentBlock->OnDestroyed.AddDynamic(this, &APlayingBoard::OnBlockDestroyed);
				BlockActors.Add(CurrentBlock);
			}
		}
	}
}

void APlayingBoard::OnBlockDestroyed(AActor* DestroyedBlock)
{
	BlockActors.Remove(Cast<ABlock>(DestroyedBlock));
}

APlayingBoard::APlayingBoard()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

}

void APlayingBoard::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ClearPreviewComponents();
	CreatePreviewComponents();
}

void APlayingBoard::BeginPlay()
{
	Super::BeginPlay();

	SpawnBlockActors();
	ClearPreviewComponents();
	
}

TSubclassOf<ABonusParent> APlayingBoard::GetBonusClass()
{
    if (BonusTypeByChance.Num() == 0 || !BonusTypeByChance[0].BonusClass)
    {
        return nullptr;
    }
    
	int32 TotalWeight = 0;

	for(const auto& CurrentBonus : BonusTypeByChance)
	{
		TotalWeight += CurrentBonus.DropChance * 100;
	}

	int32 RandomWeight = FMath::RandHelper(TotalWeight);

	for (const auto& CurrentBonus : BonusTypeByChance)
	{
		if (RandomWeight > CurrentBonus.DropChance * 100)
		{
			RandomWeight -= CurrentBonus.DropChance * 100;
		}
		else
		{
			return CurrentBonus.BonusClass;
		}
	}

	return nullptr;
}

void APlayingBoard::BonusDestroyCubes(const int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	const int32 NumToDestroy = FMath::Min(Amount, BlockActors.Num());

	for (int32 i = 0; i < NumToDestroy; i++)
	{
		const int32 RandomIndex = FMath::RandHelper(BlockActors.Num());

		if (BlockActors.IsValidIndex(RandomIndex))
		{
			BlockActors[RandomIndex]->Destroy();
		}
	}

}
