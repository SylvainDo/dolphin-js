#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object Gui_Settings_exports(Napi::Env env, Napi::Object exports) {
    // UI
    exports.Set("setThemeName", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setThemeName(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("setCurrentUserStyle", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setCurrentUserStyle(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("getCurrentUserStyle", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(IGui_Settings->getCurrentUserStyle()));
    }));
    exports.Set("setUserStylesEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setUserStylesEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("areUserStylesEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->areUserStylesEnabled());
    }));
    exports.Set("isLogVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isLogVisible());
    }));
    exports.Set("setLogVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setLogVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isLogConfigVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isLogConfigVisible());
    }));
    exports.Set("setLogConfigVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setLogConfigVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("setToolBarVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setToolBarVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isToolBarVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isToolBarVisible());
    }));
    exports.Set("setWidgetsLocked", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setWidgetsLocked(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("areWidgetsLocked", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->areWidgetsLocked());
    }));
    exports.Set("refreshWidgetVisibility", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->refreshWidgetVisibility();
        return info.Env().Undefined();
    }));
    // GameList
    exports.Set("getPaths", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        int numPaths;
        auto paths = IGui_Settings->getPaths(&numPaths);
        auto v = Napi::Array::New(info.Env(), numPaths);
        for (int i{}; i < numPaths; ++i)
            v.Set(i, fromStrUtf8(info.Env(), util::copyString(paths[i])));
        free(paths);
        return v;
    }));
    exports.Set("addPath", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->addPath(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("removePath", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->removePath(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("getPreferredView", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->getPreferredView());
    }));
    exports.Set("setPreferredView", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setPreferredView(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("getDefaultGame", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(IGui_Settings->getDefaultGame()));
    }));
    exports.Set("setDefaultGame", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setDefaultGame(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("refreshGameList", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->refreshGameList();
        return info.Env().Undefined();
    }));
    exports.Set("refreshMetadata", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->refreshMetadata();
        return info.Env().Undefined();
    }));
    exports.Set("reloadTitleDB", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->reloadTitleDB();
        return info.Env().Undefined();
    }));
    exports.Set("isAutoRefreshEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isAutoRefreshEnabled());
    }));
    exports.Set("setAutoRefreshEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setAutoRefreshEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    // Emulation
    exports.Set("getStateSlot", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGui_Settings->getStateSlot());
    }));
    exports.Set("setStateSlot", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setStateSlot(asS32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isBatchModeEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isBatchModeEnabled());
    }));
    exports.Set("setBatchModeEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setBatchModeEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isSDCardInserted", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isSDCardInserted());
    }));
    exports.Set("setSDCardInserted", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setSDCardInserted(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isUSBKeyboardConnected", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isUSBKeyboardConnected());
    }));
    exports.Set("setUSBKeyboardConnected", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setUSBKeyboardConnected(asBool(info[0]));
        return info.Env().Undefined();
    }));
    // Graphics
    exports.Set("setCursorVisibility", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setCursorVisibility(static_cast<dol_Config_ShowCursor>(asS32(info[0])));
        return info.Env().Undefined();
    }));
    exports.Set("getCursorVisibility", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGui_Settings->getCursorVisibility());
    }));
    exports.Set("setLockCursor", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setLockCursor(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("getLockCursor", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->getLockCursor());
    }));
    exports.Set("setKeepWindowOnTop", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setKeepWindowOnTop(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isKeepWindowOnTopEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isKeepWindowOnTopEnabled());
    }));
    exports.Set("getGraphicModsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->getGraphicModsEnabled());
    }));
    exports.Set("setGraphicModsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setGraphicModsEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    // Audio
    exports.Set("getVolume", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGui_Settings->getVolume());
    }));
    exports.Set("setVolume", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setVolume(asS32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("increaseVolume", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->increaseVolume(asS32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("decreaseVolume", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->decreaseVolume(asS32(info[0]));
        return info.Env().Undefined();
    }));
    // Cheats
    exports.Set("getCheatsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->getCheatsEnabled());
    }));
    exports.Set("setCheatsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setCheatsEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    // Debug
    exports.Set("setDebugModeEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setDebugModeEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isDebugModeEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isDebugModeEnabled());
    }));
    exports.Set("setRegistersVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setRegistersVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isRegistersVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isRegistersVisible());
    }));
    exports.Set("setThreadsVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setThreadsVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isThreadsVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isThreadsVisible());
    }));
    exports.Set("setWatchVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setWatchVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isWatchVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isWatchVisible());
    }));
    exports.Set("setBreakpointsVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setBreakpointsVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isBreakpointsVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isBreakpointsVisible());
    }));
    exports.Set("setCodeVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setCodeVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isCodeVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isCodeVisible());
    }));
    exports.Set("setMemoryVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setMemoryVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isMemoryVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isMemoryVisible());
    }));
    exports.Set("setNetworkVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setNetworkVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isNetworkVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isNetworkVisible());
    }));
    exports.Set("setJITVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setJITVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isJITVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Settings->isJITVisible());
    }));
    // Fallback Region
    exports.Set("getFallbackRegion", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGui_Settings->getFallbackRegion());
    }));
    exports.Set("setFallbackRegion", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Settings->setFallbackRegion(static_cast<dol_DiscIO_Region>(asS32(info[0])));
        return info.Env().Undefined();
    }));
    return exports;
}
