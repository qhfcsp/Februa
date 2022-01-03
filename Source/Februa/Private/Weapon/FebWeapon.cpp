// Copyright 2022, Choyeon. All Rights Reserved.

#include "Weapon/FebWeapon.h"

#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

AFebWeapon::AFebWeapon()
{
	bReplicates = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(TEXT("Weapon-Physics"));
	Mesh->CanCharacterStepUpOn = ECB_No;
	RootComponent = Mesh;

	Default = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	Default->SetupAttachment(Mesh, TEXT("SOCKET_Default"));

	IronSightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IronSightMesh"));
	IronSightMesh->SetupAttachment(Default);

	Grip = CreateDefaultSubobject<USceneComponent>(TEXT("Grip"));
	Grip->SetupAttachment(Mesh, TEXT("SOCKET_Grip"));

	GripMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripMesh"));
	GripMesh->SetupAttachment(Grip);

	Laser = CreateDefaultSubobject<USceneComponent>(TEXT("Laser"));
	Laser->SetupAttachment(Mesh, TEXT("SOCKET_Laser"));

	LaserMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMesh"));
	LaserMesh->SetupAttachment(Laser);

	Magazine = CreateDefaultSubobject<USceneComponent>(TEXT("Magazine"));
	Magazine->SetupAttachment(Mesh, TEXT("SOCKET_Magazine"));

	MagazineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagazineMesh"));
	MagazineMesh->SetupAttachment(Magazine);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(Mesh, TEXT("SOCKET_Muzzle"));

	MuzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuzzleMesh"));
	MuzzleMesh->SetupAttachment(Muzzle);

	Scope = CreateDefaultSubobject<USceneComponent>(TEXT("Scope"));
	Scope->SetupAttachment(Mesh, TEXT("SOCKET_Scope"));

	ScopeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScopeMesh"));
	ScopeMesh->SetupAttachment(Scope);
}

void AFebWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GetComponents(Attachments);
}
