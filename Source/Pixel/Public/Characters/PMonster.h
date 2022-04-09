// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PBaseCharacter.h"
#include "PMonster.generated.h"

class UPBattleComponent;
class UPMonsterStats;
UCLASS()
class PIXEL_API APMonster final : public APBaseCharacter
{
	GENERATED_BODY()

public:
	APMonster();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPMonsterStats> MonsterStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPBattleComponent> BattleComponent;
};
