// Basic OpenVR program to read out the GetProjectionRaw return values for both eyes

#include <stdlib.h>
#include <stdio.h>

#include <openvr.h>

constexpr uint32_t BUF_SIZE = 1024;

void readAndPrintProperty(vr::IVRSystem* pHMD, vr::TrackedDeviceIndex_t idx, vr::ETrackedDeviceProperty prop, const char* name) {
	char buffer[BUF_SIZE];
	vr::ETrackedPropertyError eError = vr::TrackedPropertyError::TrackedProp_Success;
	auto ret = pHMD->GetStringTrackedDeviceProperty(idx, prop, buffer, BUF_SIZE, &eError);
	if(ret) printf("%24s: %s\n", name, buffer);
	if(eError != vr::TrackedPropertyError::TrackedProp_Success) printf("Reading property \"%s\" failed: %s\n", name, pHMD->GetPropErrorNameFromEnum(eError));
}

int main(int argc, char *argv[])
{
	// Initialization

	vr::EVRInitError eError = vr::VRInitError_None;
	auto pHMD = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if(eError != vr::VRInitError_None) {
		printf("VR_Init failed - Unable to init VR runtime:\n%s\n", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		return -1;
	}

	vr::TrackedDeviceIndex_t hmdIndices[BUF_SIZE];
	auto numHMDS = pHMD->GetSortedTrackedDeviceIndicesOfClass(vr::TrackedDeviceClass_HMD, hmdIndices, BUF_SIZE);
	printf("Number of tracked HMDs detected: %d\n", numHMDS);
	if(numHMDS > 1) printf("(selecting the first in the list)\n");
	printf("\n");

	// Print some HMD properties

	readAndPrintProperty(pHMD, hmdIndices[0], vr::Prop_ManufacturerName_String, "HMD manufacturer");
	readAndPrintProperty(pHMD, hmdIndices[0], vr::Prop_TrackingSystemName_String, "HMD tracking system");
	readAndPrintProperty(pHMD, hmdIndices[0], vr::Prop_ModelNumber_String, "HMD model");
	readAndPrintProperty(pHMD, hmdIndices[0], vr::Prop_HardwareRevision_String, "HMD hardware revision");
	readAndPrintProperty(pHMD, hmdIndices[0], vr::Prop_DriverVersion_String, "HMD driver version");

	// Print the actual numbers we are interested in

	printf("\n-----------------------------------------------\n\nResults:\n");

	float left = 0.f, right = 0.f, top = 0.f, bottom = 0.f;
	pHMD->GetProjectionRaw(vr::Eye_Left, &left, &right, &top, &bottom);
	printf("Eye_Left:  %8.5f, %8.5f, %8.5f, %8.5f\n", left, right, top, bottom);
	pHMD->GetProjectionRaw(vr::Eye_Right, &left, &right, &top, &bottom);
	printf("Eye_Right: %8.5f, %8.5f, %8.5f, %8.5f\n", left, right, top, bottom);

	printf("\n-----------------------------------------------\n\n");
	
	// Some additional information + shutdown

	printf("NOTE: please ensure that the following conditions are met\n"
	       "      if you plan to submit your results for inclusion in\n"
	       "      the overall comparison spreadsheet:\n");
	printf(" - If the HMD has an eye relief setting, set it as close\n"
	       "   to the eye position as possible.\n");
	printf(" - If the HMD has an IPD setting, set it to the average\n"
	       "   human IPD of 64mm.\n\n");
	
	printf("How to contribute:\n  *If* your VR HMD is not included here:\n"
	       "  https://docs.google.com/spreadsheets/d/1q7Va5Q6iU40CGgewoEqRAeypUa1c0zZ86mqR8uIyDeE \n"
	       "  then please post your results here:\n"
	       "  https://metacouncil.com/threads/the-metaverse-vr-thread-hardware-software-etc-all-platforms.956 \n"
	       "  or send them to DuranteA on reddit. Thanks!\n\n");

	vr::VR_Shutdown();

	getchar();

	return 0;
}
