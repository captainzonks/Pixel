// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PBattleComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnEnded);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIXEL_API UPBattleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPBattleComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartTurn();

	UFUNCTION(BlueprintCallable)
	void EndTurn();

	UFUNCTION(BlueprintCallable)
	void StartBattle();

	UPROPERTY(BlueprintAssignable, Category = "Battle")
	FTurnEnded TurnEnded;
};
