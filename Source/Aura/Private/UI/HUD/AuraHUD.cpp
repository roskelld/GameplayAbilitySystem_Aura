// Copyright Iron Goblin Corp. 2023

#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);

		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		return OverlayWidgetController;
	} 
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// Provide crash errors if objects are not set up
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, plaese fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, plaese fill out BP_AuraHUD"));

	// Create main overly widget from overlay widget class
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	// Cast it to our widget class
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	// Set the controller params
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// Set the controller on the overlay widget
	OverlayWidget->SetWidgetController(WidgetController);

	Widget->AddToViewport();
}