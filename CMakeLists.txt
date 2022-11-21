cmake_minimum_required(VERSION 3.20)
project(dolphin-js)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(initProject)
setup_os_vars()
include(importNode)

find_package(fmt CONFIG REQUIRED)

set(SRC
    src/binding/AddressSpace.cpp
    src/binding/Config.cpp
    src/binding/Core.cpp
    src/binding/Gui_Application.cpp
    src/binding/Gui_MainWindow.cpp
    src/binding/Gui_Settings.cpp
    src/binding/JitInterface.cpp
    src/binding/Memory.cpp
    src/binding/Pad.cpp
    src/binding/UICommon.cpp
    src/binding/UICommon_GameFile.cpp
    src/binding/UICommon_GameFile.hpp
    src/binding.cpp
    src/dol.hpp
    src/dolLoader.cpp
    src/main.cpp
    src/util.cpp
    src/util.hpp
    src/valueConverter.hpp
    )

add_library(addon SHARED ${SRC})
configure_node_module(addon)
target_include_directories(addon PRIVATE ${DOL_INTERFACE})
target_link_libraries(addon PRIVATE fmt::fmt)
