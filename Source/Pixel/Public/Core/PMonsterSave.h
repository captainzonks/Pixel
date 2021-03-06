// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PMonsterStats.h"
#include "GameFramework/SaveGame.h"
#include "PMonsterSave.generated.h"

class APMonster;
/**
 * Save file for Monsters
 */
UCLASS()
class PIXEL_API UPMonsterSave : public USaveGame
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APMonster> MonsterReference;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMonsterStats MonsterStats;
};
