// © 2022, Matthew Barham. All rights reserved.


#include "Characters/PMonster.h"

#include "Components/PMonsterStats.h"

// Sets default values
APMonster::APMonster()
{
	PrimaryActorTick.bCanEverTick = false;

	MonsterStats = CreateDefaultSubobject<UPMonsterStats>(TEXT("Monster Stats"));
}

void APMonster::BeginPlay()
{
	Super::BeginPlay();
	
}
