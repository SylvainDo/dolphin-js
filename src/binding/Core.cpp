#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object Core_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("getActualEmulationSpeed", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF64(info.Env(), ICore->getActualEmulationSpeed());
    }));
    exports.Set("displayMessage", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        ICore->displayMessage(asStrUtf8(info[0]).c_str(), asS32(info[1]));
        return info.Env().Undefined();
    }));
    return exports;
}
