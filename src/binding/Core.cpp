#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object Core_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("getActualEmulationSpeed", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF64(info.Env(), ICore->getActualEmulationSpeed());
    }));
    exports.Set("isRunning", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), ICore->isRunning());
    }));
    exports.Set("isRunningAndStarted", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), ICore->isRunningAndStarted());
    }));
    exports.Set("getState", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), ICore->getState());
    }));
    exports.Set("setState", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        ICore->setState(static_cast<dol_Core_State>(asS32(info[0])));
        return info.Env().Undefined();
    }));
    exports.Set("saveScreenshot", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        if (info[0].IsUndefined()) ICore->saveScreenShot1();
        else ICore->saveScreenShot2(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("displayMessage", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        ICore->displayMessage(asStrUtf8(info[0]).c_str(), asS32(info[1]));
        return info.Env().Undefined();
    }));
    exports.Set("doFrameStep", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        ICore->doFrameStep();
        return info.Env().Undefined();
    }));
    return exports;
}
