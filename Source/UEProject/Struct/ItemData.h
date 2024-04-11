#pragma once
#include "CoreMinimal.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    EITEM_TYPE_NONE UMETA(DisplayName = "None"),

	EITEM_TYPE_DEFAULT_KNIFE  UMETA(DisplayName = "Default Knife"),

	EITEM_TYPE_DEFAULT_GUN  UMETA(DisplayName = "Default Gun"),

	EITEM_TYPE_DEFAULT_BULLET  UMETA(DisplayName = "Default Bullet"),

    EITEM_TYPE_DEFAULT_HEALTHKIT  UMETA(DisplayName = "Default HealthKit"),

    EITEM_TYPE_DEFAULT_KEY  UMETA(DisplayName = "Default Key"),
};


USTRUCT(BlueprintType)
struct UEPROJECT_API FItemData
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType = EItemType::EITEM_TYPE_NONE;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString  Name = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UTexture2D *Icon = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStackAmount = 0;
};