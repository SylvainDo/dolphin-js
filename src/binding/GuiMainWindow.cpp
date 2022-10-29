#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object GuiMainWindow_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("init", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiMainWindow->init();
        return info.Env().Undefined();
    }));
    exports.Set("shutdown", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiMainWindow->shutdown();
        return info.Env().Undefined();
    }));
    exports.Set("show", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiMainWindow->show();
        return info.Env().Undefined();
    }));
    exports.Set("requestStop", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiMainWindow->requestStop());
    }));
    exports.Set("startGame", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiMainWindow->startGame1(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    return exports;
}
