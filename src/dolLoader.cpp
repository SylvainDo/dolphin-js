#include "dol.hpp"
#include "util.hpp"

#include <cstdlib>
#include <filesystem>
#include <stdexcept>

#include <fmt/format.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

dol_AddressSpace_Accessors* IAddressSpace_Accessors;
dol_Config* IConfig;
dol_Core* ICore;
dol_Core_TitleDatabase_Factory* ICore_TitleDatabase_Factory;
dol_DolphinAnalytics* IDolphinAnalytics;
dol_Gui_Application* IGui_Application;
dol_Gui_Host* IGui_Host;
dol_Gui_MainWindow* IGui_MainWindow;
dol_Gui_Resources* IGui_Resources;
dol_Gui_Settings* IGui_Settings;
dol_Gui_Translation* IGui_Translation;
dol_JitInterface* IJitInterface;
dol_Memory* IMemory;
dol_Pad* IPad;
dol_State* IState;
dol_UICommon* IUICommon;
dol_UICommon_GameFile_Factory* IUICommon_GameFile_Factory;

static struct Loader {
    HMODULE _lib;

    void load(const std::string& libraryPath, const std::string& libraryName) {
        if (!SetDllDirectory(util::s2ws(libraryPath).c_str()))
            throw std::runtime_error(fmt::format("couldn't set dll directory ({0:#x})", GetLastError()));

        _lib = LoadLibrary((std::filesystem::path(util::s2ws(libraryPath)) /
                            std::filesystem::path(util::s2ws(libraryName))).wstring().c_str());
        if (!_lib)
            throw std::runtime_error(fmt::format("couldn't load library ({0:#x})", GetLastError()));

        const auto _setMalloc = (dol_setMalloc_t)GetProcAddress(_lib, "dol_setMalloc");
        const auto _setCalloc = (dol_setCalloc_t)GetProcAddress(_lib, "dol_setCalloc");
        const auto _setFree = (dol_setFree_t)GetProcAddress(_lib, "dol_setFree");
        if (!_setMalloc || !_setCalloc || !_setFree)
            throw std::runtime_error("couldn't load alloc setters");
        _setMalloc(malloc);
        _setCalloc(calloc);
        _setFree(free);

#define LoadInterface(x) \
        const auto _##x##_newInterface = (dol_##x##_newInterface_t)GetProcAddress(_lib, "dol_" #x "_newInterface"); \
        if (!_##x##_newInterface) \
            throw std::runtime_error("couldn't load " #x " interface"); \
        I##x = _##x##_newInterface();

        LoadInterface(AddressSpace_Accessors)
        LoadInterface(Config)
        LoadInterface(Core)
        LoadInterface(Core_TitleDatabase_Factory)
        LoadInterface(DolphinAnalytics)
        LoadInterface(Gui_Application)
        LoadInterface(Gui_Host)
        LoadInterface(Gui_MainWindow)
        LoadInterface(Gui_Resources)
        LoadInterface(Gui_Settings)
        LoadInterface(Gui_Translation)
        LoadInterface(JitInterface)
        LoadInterface(Memory)
        LoadInterface(Pad)
        LoadInterface(State)
        LoadInterface(UICommon)
        LoadInterface(UICommon_GameFile_Factory)
#undef LoadInterface
    }

    ~Loader() {
        free(IAddressSpace_Accessors);
        free(IConfig);
        free(ICore);
        free(ICore_TitleDatabase_Factory);
        free(IDolphinAnalytics);
        free(IGui_Application);
        free(IGui_Host);
        free(IGui_MainWindow);
        free(IGui_Resources);
        free(IGui_Settings);
        free(IGui_Translation);
        free(IJitInterface);
        free(IMemory);
        free(IPad);
        free(IState);
        free(IUICommon);
        free(IUICommon_GameFile_Factory);

        FreeLibrary(_lib);
    }
} s_loader;

void dolLoad(const std::string& libraryPath, const std::string& libraryName) {
    s_loader.load(libraryPath, libraryName);
}
