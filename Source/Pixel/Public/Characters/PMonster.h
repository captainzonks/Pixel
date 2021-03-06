// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PBaseCharacter.h"
#include "GameFramework/Character.h"
#include "PMonster.generated.h"

class UPMonsterStats;
UCLASS()
class PIXEL_API APMonster final : public APBaseCharacter
{
	GENERATED_BODY()

public:
	APMonster();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPMonsterStats> MonsterStats;
};
