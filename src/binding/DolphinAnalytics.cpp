#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object DolphinAnalytics_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("reloadConfig", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IDolphinAnalytics->reloadConfig();
        return info.Env().Undefined();
    }));
    exports.Set("generateNewIdentity", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IDolphinAnalytics->generateNewIdentity();
        return info.Env().Undefined();
    }));
    return exports;
}
