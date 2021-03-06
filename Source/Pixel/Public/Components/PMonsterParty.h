// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PMonsterStats.h"
#include "Components/ActorComponent.h"
#include "PMonsterParty.generated.h"

class APMonster;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIXEL_API UPMonsterParty : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPMonsterParty();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TMap<TSubclassOf<APMonster>, FMonsterStats> MonsterParty;
};
