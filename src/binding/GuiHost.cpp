#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object GuiHost_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("deleteLater", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiHost->deleteLater();
        return info.Env().Undefined();
    }));
    exports.Set("declareAsHostThread", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiHost->declareAsHostThread();
        return info.Env().Undefined();
    }));
    exports.Set("isHostThread", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IGuiHost->isHostThread());
    }));
    return exports;
}
