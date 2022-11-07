#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object Gui_Application_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("hasExited", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGui_Application->hasExited());
    }));
    return exports;
}
