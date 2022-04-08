// © 2022, Matthew Barham. All rights reserved.


#include "Characters/PBaseCharacter.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

APBaseCharacter::APBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bFootstepGate = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere"));
	TriggerSphere->SetupAttachment(RootComponent);
	TriggerSphere->SetSphereRadius(130.f);

	OnCharacterMovementUpdated.AddDynamic(this, &APBaseCharacter::Animate);

	GetCharacterMovement()->GravityScale = 2.8f;

	GetCapsuleComponent()->SetCapsuleRadius(45.f);

	GetSprite()->SetRelativeScale3D(FVector(11.f, 11.f, 11.f));
	GetSprite()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetSprite()->SetUsingAbsoluteRotation(true);
	GetSprite()->SetFlipbook(MovementFlipbooks.IdleDown);
	GetSprite()->CastShadow = true;
}

void APBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);
	OnFootstepTakenNative.AddUObject(this, &APBaseCharacter::OnFootstepNative);
}

void APBaseCharacter::OnFootstepNative()
{
	if (bFootstepGate)
	{
		bFootstepGate = !bFootstepGate;
		if (OnFootstepTaken.IsBound())
		{
			OnFootstepTaken.Broadcast();
		}
		GetWorldTimerManager().SetTimer(FootstepTimer, [this]() { bFootstepGate = true; }, 0.3f, false);
	}
}

void APBaseCharacter::Animate(float DeltaTime, FVector OldLocation, const FVector OldVelocity)
{
	TOptional<FMinimalViewInfo> ViewInfo;
	if (!IsPlayerControlled())
	{
		const UWorld* World = GetWorld();
		if (World)
		{
			if (const APlayerController* PlayerController = World->GetFirstPlayerController())
			{
				if (ACharacter* Character = PlayerController->GetCharacter())
				{
					Character->CalcCamera(DeltaTime, ViewInfo.Emplace());
				}
			}
		}
	}

	SetCurrentAnimationDirection(OldVelocity, ViewInfo);

	if (OldVelocity.Size() > 0.0f || GetCharacterMovement()->IsFalling())
	{
		switch (CurrentAnimationDirection)
		{
		case EAnimationDirection::Up:
			GetSprite()->SetFlipbook(MovementFlipbooks.WalkUp);
			break;
		case EAnimationDirection::Down:
			GetSprite()->SetFlipbook(MovementFlipbooks.WalkDown);
			break;
		case EAnimationDirection::Left:
			GetSprite()->SetFlipbook(MovementFlipbooks.WalkLeft);
			break;
		case EAnimationDirection::Right:
			GetSprite()->SetFlipbook(MovementFlipbooks.WalkRight);
			break;
		case EAnimationDirection::UpLeft:
			GetSprite()->SetFlipbook(MovementFlipbooks.WalkUpLeft);
			break;
		case EAnimationDirection::UpRight:
			GetSprite()->SetFlipbook(MovementFlipbooks.WalkUpRight);
			break;
		case EAnimationDirection::DownLeft:
			GetSprite()->SetFlipbook(MovementFlipbooks.WalkDownLeft);
			break;
		case EAnimationDirection::DownRight:
			GetSprite()->SetFlipbook(MovementFlipbooks.WalkDownRight);
			break;
		default:
			break;
		}

		if (!GetCharacterMovement()->IsFalling())
		{
			if (OnFootstepTakenNative.IsBound())
			{
				OnFootstepTakenNative.Broadcast();
			}
		}
	}
	else
	{
		switch (CurrentAnimationDirection)
		{
		case EAnimationDirection::Up:
			GetSprite()->SetFlipbook(MovementFlipbooks.IdleUp);
			break;
		case EAnimationDirection::Down:
			GetSprite()->SetFlipbook(MovementFlipbooks.IdleDown);
			break;
		case EAnimationDirection::Left:
			GetSprite()->SetFlipbook(MovementFlipbooks.IdleLeft);
			break;
		case EAnimationDirection::Right:
			GetSprite()->SetFlipbook(MovementFlipbooks.IdleRight);
			break;
		case EAnimationDirection::UpLeft:
			GetSprite()->SetFlipbook(MovementFlipbooks.IdleUpLeft);
			break;
		case EAnimationDirection::UpRight:
			GetSprite()->SetFlipbook(MovementFlipbooks.IdleUpRight);
			break;
		case EAnimationDirection::DownLeft:
			GetSprite()->SetFlipbook(MovementFlipbooks.IdleDownLeft);
			break;
		case EAnimationDirection::DownRight:
			GetSprite()->SetFlipbook(MovementFlipbooks.IdleDownRight);
			break;
		default:
			break;
		}
	}

	if (GetCharacterMovement()->IsFalling())
	{
		GetSprite()->SetPlayRate(0.f);
		GetSprite()->SetPlaybackPositionInFrames(0, true);
	}
	else
	{
		GetSprite()->SetPlayRate(1.f);
	}
}

void APBaseCharacter::SetCurrentAnimationDirection(const FVector& Velocity, TOptional<FMinimalViewInfo> ViewInfo)
{
	FVector Forward;
	FVector Right;
	if (ViewInfo.IsSet())
	{
		Forward = UKismetMathLibrary::GetForwardVector(ViewInfo.GetValue().Rotation);
		Right = UKismetMathLibrary::GetRightVector(ViewInfo.GetValue().Rotation);
	}
	else
	{
		Forward = GetActorForwardVector().GetSafeNormal();
		Right = GetActorRightVector().GetSafeNormal();
	}

	const float ForwardSpeed = FMath::Floor(FVector::DotProduct(Velocity.GetSafeNormal(), Forward) * 100) / 100;
	const float RightSpeed = FMath::Floor(FVector::DotProduct(Velocity.GetSafeNormal(), Right) * 100) / 100;

	bIsMoving = ForwardSpeed != 0.0f || RightSpeed != 0.0f;

	if (bIsMoving && !GetCharacterMovement()->IsFalling())
	{
		if (ForwardSpeed > 0.0f && abs(RightSpeed) < 0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::Up;
		}
		else if (ForwardSpeed > 0.5f && RightSpeed >= 0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::UpRight;
		}
		else if (ForwardSpeed > 0.5f && RightSpeed <= -0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::UpLeft;
		}
		else if (ForwardSpeed < 0.5f && abs(RightSpeed) <= 0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::Down;
		}
		else if (ForwardSpeed < -0.5f && RightSpeed >= 0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::DownRight;
		}
		else if (ForwardSpeed < -0.5f && RightSpeed <= -0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::DownLeft;
		}
		else if (abs(ForwardSpeed) < 0.5f && RightSpeed > 0.0f)
		{
			CurrentAnimationDirection = EAnimationDirection::Right;
		}
		else
		{
			CurrentAnimationDirection = EAnimationDirection::Left;
		}
	}
}
