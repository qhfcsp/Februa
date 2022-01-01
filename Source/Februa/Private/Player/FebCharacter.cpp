// Copyright 2021, Choyeon. All Rights Reserved.

#include "Player/FebCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AFebCharacter::AFebCharacter()
	: Camera(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")))
{
	GetCapsuleComponent()->InitCapsuleSize(22.f, 92.f);

	GetMesh()->SetRelativeLocation(FVector(4.f, 0.f, -92.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetMesh(), TEXT("SOCKET_Camera"));
	Camera->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}

void AFebCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AFebCharacter::Jumping);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AFebCharacter::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AFebCharacter::ServerCrouching);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AFebCharacter::ServerSprintingPressed);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AFebCharacter::ServerSprintingReleased);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFebCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFebCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFebCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFebCharacter::AddControllerYawInput);
}

void AFebCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFebCharacter, bCrouching);
	DOREPLIFETIME(AFebCharacter, bSprinting);
	DOREPLIFETIME(AFebCharacter, DeltaForwardAxis);
	DOREPLIFETIME(AFebCharacter, DeltaRightAxis);
	DOREPLIFETIME(AFebCharacter, PitchAxis);
}

void AFebCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (UGameplayStatics::GetPlayerCharacter(this, 0) == this && CameraShakeClass)
	{
		UGameplayStatics::GetPlayerController(this, 0)->ClientPlayCameraShake(CameraShakeClass);
	}
}

void AFebCharacter::ServerCrouching_Implementation()
{
	bCrouching = !bCrouching;

	if (bCrouching)
		bSprinting = false;
}

void AFebCharacter::ServerSprintingPressed_Implementation()
{
	bCrouching = false;
	bSprinting = true;
}

void AFebCharacter::ServerSprintingReleased_Implementation()
{
	bSprinting = false;
}

void AFebCharacter::MoveForward(float DeltaAxisValue)
{
	AddMovementInput(GetActorForwardVector(), DeltaAxisValue * (bCrouching ? 0.25f : (bSprinting && DeltaAxisValue > 0.f ? 1.f : 0.5f)));
	ServerMoveForward(DeltaAxisValue);
}

void AFebCharacter::MoveRight(float DeltaAxisValue)
{
	AddMovementInput(GetActorRightVector(), DeltaAxisValue * (bCrouching ? 0.25f : (bSprinting && DeltaForwardAxis > 0.f ? 1.f : 0.5f)));
	ServerMoveRight(DeltaAxisValue);
}

void AFebCharacter::LookUp(float DeltaAxisValue)
{
	float PrevPitchAxis = PitchAxis;
	PitchAxis = FMath::Clamp(PitchAxis + DeltaAxisValue, -30.f, 30.f);

	AddControllerPitchInput(PitchAxis - PrevPitchAxis);
	ServerLookUp(PitchAxis);
}

void AFebCharacter::ServerMoveForward_Implementation(float DeltaAxisValue)
{
	DeltaForwardAxis = DeltaAxisValue;
}

void AFebCharacter::ServerMoveRight_Implementation(float DeltaAxisValue)
{
	DeltaRightAxis = DeltaAxisValue;
}

void AFebCharacter::ServerLookUp_Implementation(float PitchAxisValue)
{
	PitchAxis = PitchAxisValue;
}
