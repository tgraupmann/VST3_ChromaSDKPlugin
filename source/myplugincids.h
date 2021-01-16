//------------------------------------------------------------------------
// Copyright(c) 2021 Razer Inc..
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace RazerInc {
//------------------------------------------------------------------------
static const Steinberg::FUID kVST3_ChromaSDKPluginProcessorUID (0xAA68CE00, 0xC5C856A8, 0xB8744C58, 0x188677FA);
static const Steinberg::FUID kVST3_ChromaSDKPluginControllerUID (0x8D9FFE1B, 0xD43C574C, 0x995C1442, 0x35D67CA5);

#define VST3_ChromaSDKPluginVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace RazerInc
