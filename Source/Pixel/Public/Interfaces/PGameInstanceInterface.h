// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PMonsterStats.h"
#include "UObject/Interface.h"
#include "PGameInstanceInterface.generated.h"

class APMonster;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to be used with the GameInstance
 */
class PIXEL_API IPGameInstanceInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SaveMonsterStats(TSubclassOf<APMonster> InMonster, const FMonsterStats& InMonsterStats);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SaveMonsterParty(const TMap<TSubclassOf<APMonster>, FMonsterStats>& InMonsterParty);
};
