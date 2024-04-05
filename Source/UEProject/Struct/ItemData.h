#pragma once
#include "CoreMinimal.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct UEPROJECT_API FItemData
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString  Name = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UTexture2D *Icon = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStackAmount = 0;
};