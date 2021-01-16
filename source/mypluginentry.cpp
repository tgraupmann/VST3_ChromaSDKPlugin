//------------------------------------------------------------------------
// Copyright(c) 2021 My Plug-in Company.
//------------------------------------------------------------------------

#include "mypluginprocessor.h"
#include "myplugincontroller.h"
#include "myplugincids.h"
#include "version.h"

#include "public.sdk/source/main/pluginfactory.h"
#include "Razer\ChromaAnimationAPI.h"

#include <tchar.h>

#define stringPluginName "VST3_ChromaSDKPlugin"

using namespace ChromaSDK;
using namespace std;


const int GetColorArraySize1D(EChromaSDKDevice1DEnum device)
{
	const int maxLeds = ChromaAnimationAPI::GetMaxLeds((int)device);
	return maxLeds;
}

const int GetColorArraySize2D(EChromaSDKDevice2DEnum device)
{
	const int maxRow = ChromaAnimationAPI::GetMaxRow((int)device);
	const int maxColumn = ChromaAnimationAPI::GetMaxColumn((int)device);
	return maxRow * maxColumn;
}


//------------------------------------------------------------------------
//  Module init/exit
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// called after library was loaded
bool InitModule ()
{
	if (ChromaAnimationAPI::InitAPI() != 0)
	{
		fprintf(stderr, "Failed to load the Chroma library!\r\n");
		return false;
	}

	ChromaSDK::APPINFOTYPE appInfo = {};

	_tcscpy_s(appInfo.Title, 256, _T("Razer VST3 Chroma SDK Plugin"));
	_tcscpy_s(appInfo.Description, 1024, _T("A sample application using Razer Chroma SDK"));
	_tcscpy_s(appInfo.Author.Name, 256, _T("Razer"));
	_tcscpy_s(appInfo.Author.Contact, 256, _T("https://developer.razer.com/chroma"));

	//appInfo.SupportedDevice = 
	//    0x01 | // Keyboards
	//    0x02 | // Mice
	//    0x04 | // Headset
	//    0x08 | // Mousepads
	//    0x10 | // Keypads
	//    0x20   // ChromaLink devices
	//    ;
	appInfo.SupportedDevice = (0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20);
	appInfo.Category = 1;

	RZRESULT result = ChromaAnimationAPI::InitSDK(&appInfo);
	if (result != RZRESULT_SUCCESS)
	{
		fprintf(stderr, "Failed to initialize Chroma!\r\n");
		return false;
	}

	Sleep(100); //Wait for ChromaSDK


	// Set default color

	const int sizeChromaLink = GetColorArraySize1D(EChromaSDKDevice1DEnum::DE_ChromaLink);
	const int sizeHeadset = GetColorArraySize1D(EChromaSDKDevice1DEnum::DE_Headset);
	const int sizeKeyboard = GetColorArraySize2D(EChromaSDKDevice2DEnum::DE_Keyboard);
	const int sizeKeypad = GetColorArraySize2D(EChromaSDKDevice2DEnum::DE_Keypad);
	const int sizeMouse = GetColorArraySize2D(EChromaSDKDevice2DEnum::DE_Mouse);
	const int sizeMousepad = GetColorArraySize1D(EChromaSDKDevice1DEnum::DE_Mousepad);

	int* colorsChromaLink = new int[sizeChromaLink];
	int* colorsHeadset = new int[sizeHeadset];
	int* colorsKeyboard = new int[sizeKeyboard];
	int* colorsKeypad = new int[sizeKeypad];
	int* colorsMouse = new int[sizeMouse];
	int* colorsMousepad = new int[sizeMousepad];

	int color = ChromaAnimationAPI::GetRGB(0, 255, 0);

	memset(colorsChromaLink, color, sizeof(int) * sizeChromaLink);
	memset(colorsHeadset, color, sizeof(int) * sizeHeadset);
	memset(colorsKeyboard, color, sizeof(int) * sizeKeyboard);
	memset(colorsKeypad, color, sizeof(int) * sizeKeypad);
	memset(colorsMouse, color, sizeof(int) * sizeMouse);
	memset(colorsMousepad, color, sizeof(int) * sizeMousepad);

	ChromaAnimationAPI::SetEffectCustom1D((int)EChromaSDKDevice1DEnum::DE_ChromaLink, colorsChromaLink);
	ChromaAnimationAPI::SetEffectCustom1D((int)EChromaSDKDevice1DEnum::DE_Headset, colorsHeadset);
	ChromaAnimationAPI::SetEffectCustom1D((int)EChromaSDKDevice1DEnum::DE_Mousepad, colorsMousepad);
	ChromaAnimationAPI::SetEffectCustom2D((int)EChromaSDKDevice2DEnum::DE_Keyboard, colorsKeyboard);
	ChromaAnimationAPI::SetEffectCustom2D((int)EChromaSDKDevice2DEnum::DE_Keypad, colorsKeypad);
	ChromaAnimationAPI::SetEffectCustom2D((int)EChromaSDKDevice2DEnum::DE_Mouse, colorsMouse);

	delete[] colorsChromaLink;
	delete[] colorsHeadset;
	delete[] colorsKeyboard;
	delete[] colorsKeypad;
	delete[] colorsMouse;
	delete[] colorsMousepad;

	return true;
}

//------------------------------------------------------------------------
// called after library is unloaded
bool DeinitModule ()
{
	ChromaAnimationAPI::StopAll();
	ChromaAnimationAPI::CloseAll();
	RZRESULT result = ChromaAnimationAPI::Uninit();
	if (result != RZRESULT_SUCCESS)
	{
		fprintf(stderr, "Failed to uninitialize Chroma!\r\n");
		return false;
	}
	return true;
}

using namespace Steinberg::Vst;
using namespace MyCompanyName;

//------------------------------------------------------------------------
//  VST Plug-in Entry
//------------------------------------------------------------------------
// Windows: do not forget to include a .def file in your project to export
// GetPluginFactory function!
//------------------------------------------------------------------------

BEGIN_FACTORY_DEF ("My Plug-in Company", 
			       "https://www.mycompanyname.com", 
			       "mailto:info@mycompanyname.com")

	//---First Plug-in included in this factory-------
	// its kVstAudioEffectClass component
	DEF_CLASS2 (INLINE_UID_FROM_FUID(kVST3_ChromaSDKPluginProcessorUID),
				PClassInfo::kManyInstances,	// cardinality
				kVstAudioEffectClass,	// the component category (do not changed this)
				stringPluginName,		// here the Plug-in name (to be changed)
				Vst::kDistributable,	// means that component and controller could be distributed on different computers
				VST3_ChromaSDKPluginVST3Category, // Subcategory for this Plug-in (to be changed)
				FULL_VERSION_STR,		// Plug-in version (to be changed)
				kVstVersionString,		// the VST 3 SDK version (do not changed this, use always this define)
				VST3_ChromaSDKPluginProcessor::createInstance)	// function pointer called when this component should be instantiated

	// its kVstComponentControllerClass component
	DEF_CLASS2 (INLINE_UID_FROM_FUID (kVST3_ChromaSDKPluginControllerUID),
				PClassInfo::kManyInstances, // cardinality
				kVstComponentControllerClass,// the Controller category (do not changed this)
				stringPluginName "Controller",	// controller name (could be the same than component name)
				0,						// not used here
				"",						// not used here
				FULL_VERSION_STR,		// Plug-in version (to be changed)
				kVstVersionString,		// the VST 3 SDK version (do not changed this, use always this define)
				VST3_ChromaSDKPluginController::createInstance)// function pointer called when this component should be instantiated

	//----for others Plug-ins contained in this factory, put like for the first Plug-in different DEF_CLASS2---

END_FACTORY
