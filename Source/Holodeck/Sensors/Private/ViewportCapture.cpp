// Fill out your copyright notice in the Description page of Project Settings.

#include "Holodeck.h"
#include "ViewportCapture.h"

// Sets default values for this component's properties
UViewportCapture::UViewportCapture(){
	PrimaryComponentTick.bCanEverTick = true;
	SensorName = "ViewportCapture";
}

void UViewportCapture::InitializeSensor() {
	UE_LOG(LogHolodeck, Log, TEXT("UViewportCapture::InitializeSensor"));
	Super::InitializeSensor();

	// This must come first, since the HolodeckSensor parent class will
	// call GetNumItems, which needs the ViewportClient.
	ViewportClient = Cast<UHolodeckViewportClient>(GEngine->GameViewport);
	if (ViewportClient && bOn) {
		const FVector2D ViewportSize = FVector2D(ViewportClient->Viewport->GetSizeXY());
		Width = ViewportSize.X;
		Height = ViewportSize.Y;
		ViewportClient->SetBuffer(Buffer);
	}
}

void UViewportCapture::TickSensorComponent(float DeltaTime,
														   ELevelTick TickType,
														   FActorComponentTickFunction* ThisTickFunction) {
	// The pixel data is captured on the rendering thread.
	// All this class needs to do is set the buffer at begin play.
	if (!ViewportClient->BufferIsSet())
		ViewportClient->SetBuffer(Buffer);
}

// Allows sensor members to be edited programmatically from client.
void UViewportCapture::EditSensorMember(FString MemberName, FString MemberValue) {
	if (MemberName == "bGrayScale") {
		bGrayScale = MemberValue.ToBool();
	}
	else if (MemberName == "Width") {
		Width = FCString::Atoi(*MemberValue);
	}
	else if (MemberName == "Height") {
		Height = FCString::Atoi(*MemberValue);
	}
}
