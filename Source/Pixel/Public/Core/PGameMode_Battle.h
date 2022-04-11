// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/PGameMode.h"
#include "PGameMode_Battle.generated.h"

UENUM(BlueprintType)
enum class EBattleState : uint8
{
	START,
	PLAYERTURN,
	ENEMYTURN,
	WON,
	LOST
};

/**
 * 
 */
UCLASS()
class PIXEL_API APGameMode_Battle final : public APGameMode
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetupBattle();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayerTurn();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EnemyTurn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	EBattleState BattleState{EBattleState::START};
};
