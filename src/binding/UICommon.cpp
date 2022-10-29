#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object UICommon_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("init", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IUICommon->init();
        return info.Env().Undefined();
    }));
    exports.Set("shutdown", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IUICommon->shutdown();
        return info.Env().Undefined();
    }));
    exports.Set("setLocale", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IUICommon->setLocale(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("createDirectories", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IUICommon->createDirectories();
        return info.Env().Undefined();
    }));
    exports.Set("setUserDirectory", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IUICommon->setUserDirectory(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("triggerSTMPowerEvent", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IUICommon->triggerSTMPowerEvent());
    }));
    exports.Set("formatSize", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(IUICommon->formatSize(asU64(info[0]), asS32(info[1]))));
    }));
    return exports;
}
