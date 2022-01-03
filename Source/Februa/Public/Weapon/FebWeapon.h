// Copyright 2022, Choyeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FebWeapon.generated.h"

UCLASS()
class FEBRUA_API AFebWeapon : public AActor
{
	GENERATED_BODY()

public:
	AFebWeapon();

	FORCEINLINE int32 GetId() const noexcept { return Id; }
	FORCEINLINE class USkeletalMeshComponent* GetMesh() const noexcept { return Mesh; }
	FORCEINLINE class USceneComponent* GetDefault() const noexcept { return Default; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UPROPERTY(EditDefaultsOnly)
	int32 Id;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY()
	class USceneComponent* Default;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* IronSightMesh;
	
	UPROPERTY()
	class USceneComponent* Grip;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* GripMesh;

	UPROPERTY()
	class USceneComponent* Laser;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* LaserMesh;

	UPROPERTY()
	class USceneComponent* Magazine;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MagazineMesh;

	UPROPERTY()
	class USceneComponent* Muzzle;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MuzzleMesh;

	UPROPERTY()
	class USceneComponent* Scope;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* ScopeMesh;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<class UStaticMeshComponent*> Attachments;
};
