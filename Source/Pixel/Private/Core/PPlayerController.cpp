// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PPlayerController.h"

void APPlayerController::SetInputMode_GameOnly_MouseConsume(APlayerController* PlayerController,
                                                            bool ConsumeCaptureMouseDown)
{
	if (PlayerController != nullptr)
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(ConsumeCaptureMouseDown);
		PlayerController->SetInputMode(InputMode);
	}
#if WITH_EDITOR
	else
	{
		FMessageLog("PIE").Error(FText::FromString("SetInputMode_GameOnly_MouseConsume expects a valid player controller as 'PlayerController' target"));
	}
#endif // WITH_EDITOR
}
