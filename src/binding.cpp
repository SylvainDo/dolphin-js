#include <napi.h>

Napi::Object Config_exports(Napi::Env env, Napi::Object exports);
Napi::Object Core_exports(Napi::Env env, Napi::Object exports);
Napi::Object DolphinAnalytics_exports(Napi::Env env, Napi::Object exports);
Napi::Object GuiApplication_exports(Napi::Env env, Napi::Object exports);
Napi::Object GuiHost_exports(Napi::Env env, Napi::Object exports);
Napi::Object GuiMainWindow_exports(Napi::Env env, Napi::Object exports);
Napi::Object GuiResources_exports(Napi::Env env, Napi::Object exports);
Napi::Object GuiSettings_exports(Napi::Env env, Napi::Object exports);
Napi::Object GuiTranslation_exports(Napi::Env env, Napi::Object exports);
Napi::Object UICommon_exports(Napi::Env env, Napi::Object exports);

Napi::Object binding_exports(Napi::Env env, Napi::Object exports) {
    auto guiNs = Napi::Object::New(env);
    guiNs.Set("Application", GuiApplication_exports(env, Napi::Object::New(env)));
    guiNs.Set("Host", GuiHost_exports(env, Napi::Object::New(env)));
    guiNs.Set("MainWindow", GuiMainWindow_exports(env, Napi::Object::New(env)));
    guiNs.Set("Resources", GuiResources_exports(env, Napi::Object::New(env)));
    guiNs.Set("Settings", GuiSettings_exports(env, Napi::Object::New(env)));
    guiNs.Set("Translation", GuiTranslation_exports(env, Napi::Object::New(env)));
    exports.Set("Gui", guiNs);
    exports.Set("Config", Config_exports(env, Napi::Object::New(env)));
    exports.Set("Core", Core_exports(env, Napi::Object::New(env)));
    exports.Set("DolphinAnalytics", DolphinAnalytics_exports(env, Napi::Object::New(env)));
    exports.Set("UICommon", UICommon_exports(env, Napi::Object::New(env)));
    return exports;
}
