#include <napi.h>

Napi::Object AddressSpace_exports(Napi::Env env, Napi::Object exports);
Napi::Object Config_exports(Napi::Env env, Napi::Object exports);
Napi::Object Core_exports(Napi::Env env, Napi::Object exports);
Napi::Object Gui_Application_exports(Napi::Env env, Napi::Object exports);
Napi::Object Gui_MainWindow_exports(Napi::Env env, Napi::Object exports);
Napi::Object Gui_Settings_exports(Napi::Env env, Napi::Object exports);
Napi::Object JitInterface_exports(Napi::Env env, Napi::Object exports);
Napi::Object Memory_exports(Napi::Env env, Napi::Object exports);
Napi::Object Pad_exports(Napi::Env env, Napi::Object exports);
Napi::Object UICommon_exports(Napi::Env env, Napi::Object exports);
Napi::Object Util_exports(Napi::Env env, Napi::Object exports);

Napi::Object binding_exports(Napi::Env env, Napi::Object exports) {
    auto guiNs = Napi::Object::New(env);
    guiNs.Set("Application", Gui_Application_exports(env, Napi::Object::New(env)));
    guiNs.Set("MainWindow", Gui_MainWindow_exports(env, Napi::Object::New(env)));
    guiNs.Set("Settings", Gui_Settings_exports(env, Napi::Object::New(env)));
    exports.Set("Gui", guiNs);
    exports.Set("AddressSpace", AddressSpace_exports(env, Napi::Object::New(env)));
    exports.Set("Config", Config_exports(env, Napi::Object::New(env)));
    exports.Set("Core", Core_exports(env, Napi::Object::New(env)));
    exports.Set("JitInterface", JitInterface_exports(env, Napi::Object::New(env)));
    exports.Set("Memory", Memory_exports(env, Napi::Object::New(env)));
    exports.Set("Pad", Pad_exports(env, Napi::Object::New(env)));
    exports.Set("UICommon", UICommon_exports(env, Napi::Object::New(env)));
    exports.Set("Util", Util_exports(env, Napi::Object::New(env)));
    return exports;
}
