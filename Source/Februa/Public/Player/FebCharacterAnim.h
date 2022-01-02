// Copyright 2021, Choyeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FebCharacterAnim.generated.h"

UCLASS()
class FEBRUA_API UFebCharacterAnim : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float DeltaForwardAxis;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float DeltaRightAxis;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float PitchAxis;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bJumping;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bCrouching;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bSprinting;

	class AFebCharacter* Owner;
};
