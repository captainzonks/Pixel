// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PMonsterStats.generated.h"

USTRUCT(BlueprintType)
struct PIXEL_API FMonsterStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int XP{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level{1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOwned{false};
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PIXEL_API UPMonsterStats final : public UActorComponent
{
	GENERATED_BODY()

public:
	UPMonsterStats();

	FMonsterStats GetMonsterStats() const { return MonsterStats; }
	FMonsterStats& ModifyMonsterStats() { return MonsterStats; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FMonsterStats MonsterStats;
};
