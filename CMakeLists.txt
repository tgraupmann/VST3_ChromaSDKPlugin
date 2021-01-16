cmake_minimum_required(VERSION 3.14.0)

set(vst3sdk_SOURCE_DIR C:/Users/timot/Downloads/vst-sdk_3.7.1_build-50_2020-11-17/VST_SDK/VST3_SDK)
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(VST3_ChromaSDKPlugin)
  
set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(VST3_ChromaSDKPlugin     
    source/version.h
    source/myplugincids.h
    source/mypluginprocessor.h
    source/mypluginprocessor.cpp
    source/myplugincontroller.h
    source/myplugincontroller.cpp
    source/mypluginentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
	target_sources(VST3_ChromaSDKPlugin
		PRIVATE
			resource/myplugineditor.uidesc
	)
    target_link_libraries(VST3_ChromaSDKPlugin
        PRIVATE
            vstgui_support
    )
    smtg_add_vst3_resource(VST3_ChromaSDKPlugin "resource/myplugineditor.uidesc")
endif()
# -------------------

smtg_add_vst3_snapshot(VST3_ChromaSDKPlugin resource/AA68CE00C5C856A8B8744C58188677FA_snapshot.png)
smtg_add_vst3_snapshot(VST3_ChromaSDKPlugin resource/AA68CE00C5C856A8B8744C58188677FA_snapshot_2.0x.png)

target_link_libraries(VST3_ChromaSDKPlugin
    PRIVATE
        sdk
)

if(SMTG_MAC)
    smtg_set_bundle(VST3_ChromaSDKPlugin INFOPLIST 
        "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" 
        PREPROCESS
    )
elseif(SMTG_WIN)
    target_sources(VST3_ChromaSDKPlugin PRIVATE 
        resource/win32resource.rc
    )
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT VST3_ChromaSDKPlugin)
	
	set_target_properties(VST3_ChromaSDKPlugin PROPERTIES
		VS_DEBUGGER_COMMAND
			"$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
		VS_DEBUGGER_COMMAND_ARGUMENTS
			" --pluginfolder \"$(OutDir)\" "
	)
endif()


