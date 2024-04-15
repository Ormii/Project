// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseExamination.generated.h"

UCLASS()
class UEPROJECT_API ABaseExamination : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseExamination();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent *GetItemMesh(){return ItemMesh;}

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *ItemMesh;
};
