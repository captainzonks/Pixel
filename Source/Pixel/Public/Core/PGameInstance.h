// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/PGameInstanceInterface.h"
#include "PGameInstance.generated.h"

/**
 * GameInstance for Pixel game
 */
UCLASS()
class PIXEL_API UPGameInstance : public UGameInstance, public IPGameInstanceInterface
{
	GENERATED_BODY()

};
