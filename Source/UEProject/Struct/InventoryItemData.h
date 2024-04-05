#pragma once
#include "CoreMinimal.h"
#include "InventoryItemData.generated.h"

USTRUCT(BlueprintType)
struct UEPROJECT_API FInventoryItemData
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class ABaseItem  *Item = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Amount = 0;
};