// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PBaseCharacter.generated.h"

class USphereComponent;
class UPaperFlipbook;
/** Enums for each possible direction to face */
UENUM(BlueprintType)
enum class EAnimationDirection : uint8
{
	Down,
	Up,
	Right,
	Left,
	DownRight,
	DownLeft,
	UpRight,
	UpLeft
};

/** Flipbooks which hold the different possible directions of movement */
USTRUCT(BlueprintType)
struct PIXEL_API FMovementFlipbooks
{
	GENERATED_BODY()

	// Idle

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleDownRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleDownLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleUpRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleUpLeft;

	// Walking

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkDownRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkDownLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkUpRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkUpLeft;
};

/** Delegate called when a footstep is made */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFootstepTaken);
DECLARE_MULTICAST_DELEGATE(FOnFootstepTakenNative);

/**
 * 
 */
UCLASS()
class PIXEL_API APBaseCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APBaseCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UTFileData* GetFileDataComponent() const {return FileDataComponent;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**********************************
	 *       Delegates & Events
	 **********************************/

	/**
	* Called upon movement, with a timer delay of 0.3 seconds.
	* Use for footstep sound or particle effects in Blueprints.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnFootstep();
	void OnFootstepNative();

	/* Broadcast when the Flipbook animation is walking */
	UPROPERTY(BlueprintAssignable, Category="Delegates")
	FOnFootstepTaken OnFootstepTaken;
	FOnFootstepTakenNative OnFootstepTakenNative;

	/**********************************
	 *           Animation
	 **********************************/

	/**
	 * Animates the sprite with Editor-set Flipbooks for movement. This function is called
	 * by binding it to the OnCharacterMovementUpdated delegate. Direction is selected by
	 * calling SetCurrentAnimationDirection().
	 * @param DeltaTime Time since last frame.
	 * @param OldLocation Location at call.
	 * @param OldVelocity Velocity at call.
	 */
	UFUNCTION()
	void Animate(float DeltaTime, FVector OldLocation, const FVector OldVelocity);

	/**
	 * Sets the CurrentAnimationDirection enum by detecting velocity and the Player's camera rotation
	 * in world space via the provided ViewInfo. If ViewInfo is not set, the function returns early.
	 * @param Velocity Actor's velocity at time of call.
	 * @param ViewInfo Player's camera information.
	 */
	virtual void SetCurrentAnimationDirection(const FVector& Velocity, TOptional<FMinimalViewInfo> ViewInfo);

	/**************************/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> TriggerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	EAnimationDirection CurrentAnimationDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FMovementFlipbooks MovementFlipbooks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	uint8 bIsMoving:1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	uint8 bFootstepGate:1;

	FTimerHandle FootstepTimer;
};
