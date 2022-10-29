#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object GuiApplication_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("init", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiApplication->init();
        return info.Env().Undefined();
    }));
    exports.Set("shutdown", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiApplication->shutdown();
        return info.Env().Undefined();
    }));
    exports.Set("hasExited", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiApplication->hasExited());
    }));
    exports.Set("processEvents", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiApplication->processEvents3();
        return info.Env().Undefined();
    }));
    return exports;
}
