// © 2022, Matthew Barham. All rights reserved.


#include "Components/PBattleComponent.h"

UPBattleComponent::UPBattleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UPBattleComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UPBattleComponent::StartTurn()
{
}

void UPBattleComponent::EndTurn()
{
}

void UPBattleComponent::StartBattle()
{
}
