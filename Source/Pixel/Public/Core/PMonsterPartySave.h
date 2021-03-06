// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PMonsterStats.h"
#include "GameFramework/SaveGame.h"
#include "PMonsterPartySave.generated.h"

class APMonster;
/**
 * Save for monsters in a player or AI's party
 */
UCLASS()
class PIXEL_API UPMonsterPartySave : public USaveGame
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TMap<TSubclassOf<APMonster>, FMonsterStats> MonsterParty;
};
