#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object GuiSettings_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("unregisterDevicesChangedCallback", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->unregisterDevicesChangedCallback();
        return info.Env().Undefined();
    }));
    // UI
    exports.Set("setThemeName", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setThemeName(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("setCurrentUserStyle", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setCurrentUserStyle(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("getCurrentUserStyle", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(IGuiSettings->getCurrentUserStyle()));
    }));
    exports.Set("setUserStylesEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setUserStylesEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("areUserStylesEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->areUserStylesEnabled());
    }));
    exports.Set("isLogVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isLogVisible());
    }));
    exports.Set("setLogVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setLogVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isLogConfigVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isLogConfigVisible());
    }));
    exports.Set("setLogConfigVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setLogConfigVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("setToolBarVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setToolBarVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isToolBarVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isToolBarVisible());
    }));
    exports.Set("setWidgetsLocked", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setWidgetsLocked(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("areWidgetsLocked", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->areWidgetsLocked());
    }));
    exports.Set("refreshWidgetVisibility", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->refreshWidgetVisibility();
        return info.Env().Undefined();
    }));
    // GameList
    exports.Set("getPaths", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        int numPaths;
        auto paths = IGuiSettings->getPaths(&numPaths);
        auto v = Napi::Array::New(info.Env(), numPaths);
        for (int i{}; i < numPaths; ++i)
            v.Set(i, fromStrUtf8(info.Env(), util::copyString(paths[i])));
        free(paths);
        return v;
    }));
    exports.Set("addPath", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->addPath(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("removePath", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->removePath(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("getPreferredView", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->getPreferredView());
    }));
    exports.Set("setPreferredView", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setPreferredView(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("getDefaultGame", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(IGuiSettings->getDefaultGame()));
    }));
    exports.Set("setDefaultGame", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setDefaultGame(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("refreshGameList", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->refreshGameList();
        return info.Env().Undefined();
    }));
    exports.Set("notifyRefreshGameListStarted", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->notifyRefreshGameListStarted();
        return info.Env().Undefined();
    }));
    exports.Set("notifyRefreshGameListComplete", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->notifyRefreshGameListComplete();
        return info.Env().Undefined();
    }));
    exports.Set("refreshMetadata", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->refreshMetadata();
        return info.Env().Undefined();
    }));
    exports.Set("notifyMetadataRefreshComplete", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->notifyMetadataRefreshComplete();
        return info.Env().Undefined();
    }));
    exports.Set("reloadTitleDB", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->reloadTitleDB();
        return info.Env().Undefined();
    }));
    exports.Set("isAutoRefreshEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isAutoRefreshEnabled());
    }));
    exports.Set("setAutoRefreshEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setAutoRefreshEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    // Emulation
    exports.Set("getStateSlot", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGuiSettings->getStateSlot());
    }));
    exports.Set("setStateSlot", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setStateSlot(asS32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isBatchModeEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isBatchModeEnabled());
    }));
    exports.Set("setBatchModeEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setBatchModeEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isSDCardInserted", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isSDCardInserted());
    }));
    exports.Set("setSDCardInserted", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setSDCardInserted(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isUSBKeyboardConnected", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isUSBKeyboardConnected());
    }));
    exports.Set("setUSBKeyboardConnected", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setUSBKeyboardConnected(asBool(info[0]));
        return info.Env().Undefined();
    }));
    // Graphics
    exports.Set("setCursorVisibility", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setCursorVisibility(static_cast<dolConfigShowCursor>(asS32(info[0])));
        return info.Env().Undefined();
    }));
    exports.Set("getCursorVisibility", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGuiSettings->getCursorVisibility());
    }));
    exports.Set("setLockCursor", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setLockCursor(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("getLockCursor", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->getLockCursor());
    }));
    exports.Set("setKeepWindowOnTop", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setKeepWindowOnTop(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isKeepWindowOnTopEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isKeepWindowOnTopEnabled());
    }));
    exports.Set("getGraphicModsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->getGraphicModsEnabled());
    }));
    exports.Set("setGraphicModsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setGraphicModsEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    // Audio
    exports.Set("getVolume", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGuiSettings->getVolume());
    }));
    exports.Set("setVolume", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setVolume(asS32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("increaseVolume", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->increaseVolume(asS32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("decreaseVolume", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->decreaseVolume(asS32(info[0]));
        return info.Env().Undefined();
    }));
    // Cheats
    exports.Set("getCheatsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->getCheatsEnabled());
    }));
    exports.Set("setCheatsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setCheatsEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    // Debug
    exports.Set("setDebugModeEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setDebugModeEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isDebugModeEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isDebugModeEnabled());
    }));
    exports.Set("setRegistersVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setRegistersVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isRegistersVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isRegistersVisible());
    }));
    exports.Set("setThreadsVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setThreadsVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isThreadsVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isThreadsVisible());
    }));
    exports.Set("setWatchVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setWatchVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isWatchVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isWatchVisible());
    }));
    exports.Set("setBreakpointsVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setBreakpointsVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isBreakpointsVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isBreakpointsVisible());
    }));
    exports.Set("setCodeVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setCodeVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isCodeVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isCodeVisible());
    }));
    exports.Set("setMemoryVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setMemoryVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isMemoryVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isMemoryVisible());
    }));
    exports.Set("setNetworkVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setNetworkVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isNetworkVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isNetworkVisible());
    }));
    exports.Set("setJITVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setJITVisible(asBool(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("isJITVisible", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isJITVisible());
    }));
    // Auto-Update
    exports.Set("getAutoUpdateTrack", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(IGuiSettings->getAutoUpdateTrack()));
    }));
    exports.Set("setAutoUpdateTrack", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setAutoUpdateTrack(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    // Fallback Region
    exports.Set("getFallbackRegion", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGuiSettings->getFallbackRegion());
    }));
    exports.Set("setFallbackRegion", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setFallbackRegion(static_cast<dolDiscIORegion>(asS32(info[0])));
        return info.Env().Undefined();
    }));
    // Analytics
    exports.Set("isAnalyticsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiSettings->isAnalyticsEnabled());
    }));
    exports.Set("setAnalyticsEnabled", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiSettings->setAnalyticsEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    return exports;
}
