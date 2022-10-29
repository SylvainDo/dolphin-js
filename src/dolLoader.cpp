#include "dol.hpp"
#include "util.hpp"

#include <cstdlib>
#include <filesystem>
#include <stdexcept>

#include <fmt/format.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

dolConfig* IConfig;
dolCore* ICore;
dolDolphinAnalytics* IDolphinAnalytics;
dolGuiApplication* IGuiApplication;
dolGuiHost* IGuiHost;
dolGuiMainWindow* IGuiMainWindow;
dolGuiResources* IGuiResources;
dolGuiSettings* IGuiSettings;
dolGuiTranslation* IGuiTranslation;
dolUICommon* IUICommon;

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
        _setMalloc(malloc);
        const auto _setCalloc = (dol_setCalloc_t)GetProcAddress(_lib, "dol_setCalloc");
        _setCalloc(calloc);
        const auto _setFree = (dol_setFree_t)GetProcAddress(_lib, "dol_setFree");
        _setFree(free);

#define LoadInterface(x) \
        const auto _##x##_newInterface = (dol##x##_newInterface_t)GetProcAddress(_lib, "dol" #x "_newInterface"); \
        I##x = _##x##_newInterface();

        LoadInterface(Config)
        LoadInterface(Core)
        LoadInterface(DolphinAnalytics)
        LoadInterface(GuiApplication)
        LoadInterface(GuiHost)
        LoadInterface(GuiMainWindow)
        LoadInterface(GuiResources)
        LoadInterface(GuiSettings)
        LoadInterface(GuiTranslation)
        LoadInterface(UICommon)
#undef LoadInterface
    }

    ~Loader() {
        free(IConfig);
        free(ICore);
        free(IDolphinAnalytics);
        free(IGuiApplication);
        free(IGuiHost);
        free(IGuiMainWindow);
        free(IGuiResources);
        free(IGuiSettings);
        free(IGuiTranslation);
        free(IUICommon);

        FreeLibrary(_lib);
    }
} s_loader;

void dolLoad(const std::string& libraryPath, const std::string& libraryName) {
    s_loader.load(libraryPath, libraryName);
}
