// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPSHUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "FPSCharacter.h"
#include "Blueprint/WidgetTree.h"

void UFPSHUDWidget::UpdateHealth(int32 CurrentHealth)
{
	if (HealthText)
	{
		HealthText->SetText(FText::FromString(FString::Printf(TEXT("Health: %d"),CurrentHealth)));
	}
}

void UFPSHUDWidget::UpdateAmmo(int32 CurrentAmmo, int32 MaxAmmo)
{
	if (AmmoText)
	{
		AmmoText->SetText(FText::FromString(FString::Printf(TEXT("Ammo: %d / %d"), CurrentAmmo, MaxAmmo)));
	}
}

void UFPSHUDWidget::ShowReloadBar(float Duration)
{
	if (ReloadBar)
	{
		AmmoText->SetVisibility(ESlateVisibility::Hidden);
		ReloadDuration = Duration;
		ReloadElapsedTime = 0.0f;
		ReloadBar->SetPercent(0.0f);

		ReloadBar->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().SetTimer(
			ReloadTimerHandle,
			this,
			&UFPSHUDWidget::UpdateReloadBar,
			0.01f,
			true
		);
	}
}

void UFPSHUDWidget::PlayDamageFlash(float Duration)
{
	if (DamageFlashImage)
	{
		DamageFlashImage->SetVisibility(ESlateVisibility::Visible);
		FTimerHandle DamageTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, FTimerDelegate::CreateLambda([this]()
			{
				DamageFlashImage->SetVisibility(ESlateVisibility::Hidden);
			}), Duration, false);
	}
}

void UFPSHUDWidget::UpdateMinimapIcons(const TArray<AActor*>& TrackedActors, UTexture2D* IconTexture)
{
	if (!MinimapActor || !MinimapCanvas || !IconTexture)
	{
		return;
	}

	MinimapCanvas->ClearChildren();
	FVector2D MinimapSize = MinimapCanvas->GetCachedGeometry().GetLocalSize();

	FVector2D PlayerIconPosition(MinimapSize.X/2, MinimapSize.Y/2); // top be set with the algorithm

	UImage* PlayerIcon = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
	PlayerIcon->SetBrushFromTexture(IconTexture);

	constexpr double PlayerIconSize = 16.0f;

	UCanvasPanelSlot* PlayerIconSlot = MinimapCanvas->AddChildToCanvas(PlayerIcon);
	if (PlayerIconSlot)
	{
		PlayerIconSlot->SetPosition(PlayerIconPosition);
		PlayerIconSlot->SetSize(FVector2D(PlayerIconSize, PlayerIconSize));
		PlayerIconSlot->SetAutoSize(false);
	}

	FVector CaptureCenter3D = MinimapActor->GetActorLocation();
	//FRotator CaptureRotation = MinimapActor->MinimapCaptureComponent->GetComponentRotation();
	FRotator CaptureRotation = MinimapActor->GetActorRotation();
	double OrthoWidth = MinimapActor->MinimapCaptureComponent->OrthoWidth;
	FRotator CaptureYawOnly(0.0, CaptureRotation.Yaw, 0.0);
	constexpr double IconSize = 16.0f;

	for (AActor* Actor : TrackedActors)
	{
		if (!Actor)
		{
			continue;
		}

		FVector ActorWorldPos = Actor->GetActorLocation();
		FVector RelativeActorPos = ActorWorldPos - CaptureCenter3D;
		FVector ActorLocationBasedOnPlayerYaw = CaptureYawOnly.UnrotateVector(RelativeActorPos);

		// Normalize: Bring relative actor pos between -0.5 and 0.5
		// Mind x and y axis inversion when porting to 2D dimension
		double NormX = ActorLocationBasedOnPlayerYaw.Y / OrthoWidth;
		double NormY = ActorLocationBasedOnPlayerYaw.X / OrthoWidth;

		// Bring normalized pos between 0 and 1. On Y axis let's invert them to keep y increasing from top to bottom
		NormX = NormX + 0.5f;
		NormY = 1.0f - (NormY + 0.5);
		
		//ensure the range is strictly between 0 and 1
		NormX = FMath::Clamp(NormX, 0.0f, 1.0f);
		NormY = FMath::Clamp(NormY, 0.0f, 1.0f);

		// Bring the normalized 0-1 pos into the range 0, minimapsize
		FVector2D IconPosition(NormX * MinimapSize.X - IconSize/2, NormY * MinimapSize.Y - IconSize/2);
		

		if (IconPosition.X > 0 && IconPosition.X < MinimapSize.X && IconPosition.Y > 0 && IconPosition.Y < MinimapSize.Y)
		{
			// use the converted position to place the icon in the minimap
			UImage* Icon = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
			Icon->SetBrushFromTexture(IconTexture);

			UCanvasPanelSlot* IconSlot = MinimapCanvas->AddChildToCanvas(Icon);
			if (IconSlot)
			{
				IconSlot->SetPosition(IconPosition);
				IconSlot->SetSize(FVector2D(IconSize, IconSize));
				IconSlot->SetAutoSize(false);
			}
		}
	}
}

void UFPSHUDWidget::UpdateReloadBar()
{
	ReloadElapsedTime += 0.01f;

	//Calculate percentage to fill
	float Percent = FMath::Clamp(ReloadElapsedTime / ReloadDuration, 0.0f, 1.0f);
	ReloadBar->SetPercent(Percent);

	if(ReloadElapsedTime>= ReloadDuration)
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
		ReloadBar->SetVisibility(ESlateVisibility::Hidden);
		AmmoText->SetVisibility(ESlateVisibility::Visible);
	}
}
