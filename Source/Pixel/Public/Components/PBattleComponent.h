// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PBattleComponent.generated.h"

class UPMonsterAbility;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnEnded);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PIXEL_API UPBattleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPBattleComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartTurn();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EndTurn();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartRound();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RequestTurn();

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Battle")
	FTurnEnded TurnEnded;
};
