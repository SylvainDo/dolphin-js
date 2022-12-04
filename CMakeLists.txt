cmake_minimum_required(VERSION 3.20)
project(dolphin-js)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(initProject)
setup_os_vars()
include(importNode)

set(SRC
    src/binding/AddressSpace.cpp
    src/binding/Config.cpp
    src/binding/Core.cpp
    src/binding/Gui_Application.cpp
    src/binding/Gui_MainWindow.cpp
    src/binding/Gui_Q_Action.cpp
    src/binding/Gui_Q_Action.hpp
    src/binding/Gui_Q_CommonDialogs.cpp
    src/binding/Gui_Q_Menu.cpp
    src/binding/Gui_Q_Menu.hpp
    src/binding/Gui_Q_MenuBar.cpp
    src/binding/Gui_Q_MenuBar.hpp
    src/binding/Gui_Q_MenuEtc.cpp
    src/binding/Gui_Settings.cpp
    src/binding/JitInterface.cpp
    src/binding/Memory.cpp
    src/binding/Pad.cpp
    src/binding/State.cpp
    src/binding/UICommon.cpp
    src/binding/UICommon_GameFile.cpp
    src/binding/UICommon_GameFile.hpp
    src/binding/Util.cpp
    src/binding.cpp
    src/dol.hpp
    src/dolLoader.cpp
    src/main.cpp
    src/pointerWrap.cpp
    src/pointerWrap.hpp
    src/util.cpp
    src/util.hpp
    src/valueConverter.hpp
    )

add_library(addon SHARED ${SRC})
configure_node_module(addon)
target_include_directories(addon PRIVATE ${DOL_INTERFACE})
