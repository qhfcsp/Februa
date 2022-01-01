// Copyright 2021, Choyeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FebCharacter.generated.h"

UCLASS()
class FEBRUA_API AFebCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFebCharacter();

	FORCEINLINE bool IsCrouching() const { return bCrouching; }
	FORCEINLINE bool IsSprinting() const { return bSprinting; }
	FORCEINLINE float GetDeltaForwardAxis() const { return DeltaForwardAxis; }
	FORCEINLINE float GetDeltaRightAxis() const { return DeltaRightAxis; }
	FORCEINLINE float GetPitchAxis() const { return PitchAxis; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Landed(const FHitResult& Hit) override;

private:
	void Jumping() { if (bCrouching) ServerCrouching(); else Jump(); }

	UFUNCTION(Server, Reliable)
	void ServerCrouching();

	UFUNCTION(Server, Reliable)
	void ServerSprintingPressed();

	UFUNCTION(Server, Reliable)
	void ServerSprintingReleased();

	void MoveForward(float DeltaAxisValue);
	void MoveRight(float DeltaAxisValue);
	void LookUp(float DeltaAxisValue);

	UFUNCTION(Server, Unreliable)
	void ServerMoveForward(float DeltaAxisValue);

	UFUNCTION(Server, Unreliable)
	void ServerMoveRight(float DeltaAxisValue);

	UFUNCTION(Server, Unreliable)
	void ServerLookUp(float PitchAxisValue);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;

	UPROPERTY(Replicated)
	bool bCrouching = false;

	UPROPERTY(Replicated)
	bool bSprinting = false;

	UPROPERTY(Replicated)
	float DeltaForwardAxis;

	UPROPERTY(Replicated)
	float DeltaRightAxis;

	UPROPERTY(Replicated)
	float PitchAxis;
};
