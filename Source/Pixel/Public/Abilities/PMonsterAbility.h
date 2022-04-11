// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PMonsterAbility.generated.h"

UENUM(BlueprintType)
enum class EMonsterAbilityType : uint8
{
	NONE,
	DAMAGE,
	HEAL
};

/**
 * Base Monster Ability class
 */
UCLASS(Blueprintable)
class PIXEL_API UPMonsterAbility : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	EMonsterAbilityType AbilityType{EMonsterAbilityType::NONE};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	float Modifier{};
};
