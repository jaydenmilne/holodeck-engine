#include "Holodeck.h"
#include "RGBCamera.h"

URGBCamera::URGBCamera() {
	SensorName = "RGBCamera";
}

void URGBCamera::InitializeSensor() {
	Super::InitializeSensor();

	//Set up everything for the scenecapturecomponent2d
	SceneCapture->CaptureSource = SCS_FinalColorLDR; //Pick what type of output you want to be sent to the texture target. 	
}

void URGBCamera::TickSensorComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	TickCounter++;
	if (TickCounter == TicksPerCapture) {
		RenderRequest.RetrievePixels(Buffer, TargetTexture);
		TickCounter = 0;
	}
}

// Allows sensor members to be edited programmatically from client.
void URGBCamera::EditSensorMember(FString MemberName, FString MemberValue) {
	if (MemberName == "TicksPerCapture") {
		TicksPerCapture = FCString::Atoi(*MemberValue);
	}
}
