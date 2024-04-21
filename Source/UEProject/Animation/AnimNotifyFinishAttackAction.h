// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "AnimNotifyFinishAttackAction.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UAnimNotifyFinishAttackAction : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
};
