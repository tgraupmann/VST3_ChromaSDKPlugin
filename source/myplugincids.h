//------------------------------------------------------------------------
// Copyright(c) 2021 Razer Inc.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace ChromaSDK {
//------------------------------------------------------------------------
static const Steinberg::FUID kVST3_ChromaSDKPluginProcessorUID (0xEC55FC9C, 0x8A4F5830, 0x82EE14E6, 0xC1173354);
static const Steinberg::FUID kVST3_ChromaSDKPluginControllerUID (0xB8A2D462, 0x70AB5FB4, 0xAC736E52, 0x416956A4);

#define VST3_ChromaSDKPluginVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace ChromaSDK
