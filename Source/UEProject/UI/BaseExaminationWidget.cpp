// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor.h"
#include "BasePlayerController.h"
#include "BaseExamination.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Compo/InventoryComponent.h"
#include "UI/BaseExaminationWidget.h"


FReply UBaseExaminationWidget::NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent )
{
    if(SurvivorRef)
    {
        UE_LOG(LogTemp, Warning, TEXT("MouseButton Down"));
        RotateMesh = true;
        ABasePlayerController *PlayerController = Cast<ABasePlayerController>(SurvivorRef->GetController());
        if(PlayerController)
        {
            float LocationX = 0.0f, LocationY = 0.0f;
            float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
            PlayerController->GetMousePosition(LocationX, LocationY);

            MouseLocation = FVector2D{LocationX*(1.0f/ViewportScale),LocationY*(1.0f/ViewportScale)};
        }
    }

    return FReply::Handled();
}

FReply UBaseExaminationWidget::NativeOnMouseMove( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent )
{
    auto ReturnValue = OnMouseMove( InGeometry, InMouseEvent ).NativeReply;

    if(RotateMesh == false)
        return ReturnValue;

    if(SurvivorRef == nullptr)
        return ReturnValue;

    UInventoryComponent* InventoryComponent = SurvivorRef->GetInventoryComponent();
    if(InventoryComponent == nullptr)
        return ReturnValue;

    ABaseExamination *ExaminationActor = InventoryComponent->GetExaminationActor();
    if(ExaminationActor == nullptr)
        return ReturnValue;

    UStaticMeshComponent *ItemMesh = ExaminationActor->GetItemMesh();
    if(ItemMesh == nullptr)
        return ReturnValue;

    ABasePlayerController *PlayerController = Cast<ABasePlayerController>(SurvivorRef->GetController());
    if(PlayerController == nullptr)
        return ReturnValue;

    float LocationX = 0.0f, LocationY = 0.0f;
    float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
    PlayerController->GetMousePosition(LocationX, LocationY);

    FVector2D MousePositionScaledByDPI = FVector2D{LocationX*(1.0f/ViewportScale),LocationY*(1.0f/ViewportScale)};

    FVector2D DeltaVector2D = MousePositionScaledByDPI - MouseLocation;
    ItemMesh->AddWorldRotation(FRotator{0.0f,-DeltaVector2D.X,DeltaVector2D.Y});

    MouseLocation = MousePositionScaledByDPI;

    return FReply::Unhandled();
}

FReply UBaseExaminationWidget::NativeOnMouseButtonUp( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent )
{
    UE_LOG(LogTemp, Warning, TEXT("MouseButton Up"));
    RotateMesh = false;
    
    return FReply::Unhandled();
}