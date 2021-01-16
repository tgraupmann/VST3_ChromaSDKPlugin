//------------------------------------------------------------------------
// Copyright(c) 2021 Razer Inc.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace ChromaSDK {
//------------------------------------------------------------------------
static const Steinberg::FUID kVST3_ChromaSDKPluginProcessorUID (0xE5E82FE6, 0x21AF5C65, 0x8AE3B9F1, 0xA1FB5212);
static const Steinberg::FUID kVST3_ChromaSDKPluginControllerUID (0x167E2346, 0x6B915492, 0xBB7D91BD, 0x501F9FBC);

#define VST3_ChromaSDKPluginVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace ChromaSDK
