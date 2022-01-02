// Copyright 2021, Choyeon. All Rights Reserved.

#include "Player/FebCharacterAnim.h"
#include "Player/FebCharacter.h"

#include "GameFramework/PawnMovementComponent.h"

void UFebCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Owner)
	{
		DeltaForwardAxis = -Owner->GetDeltaForwardAxis();
		DeltaRightAxis = Owner->GetDeltaRightAxis();
		PitchAxis = Owner->GetPitchAxis() * 2.5f;
		bJumping = !Owner->CanJump();
		bCrouching = Owner->IsCrouching();
		bSprinting = Owner->IsSprinting();
	}
	else
	{
		Owner = Cast<AFebCharacter>(TryGetPawnOwner());
	}
}
