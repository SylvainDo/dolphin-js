#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object Pad_exports(Napi::Env env, Napi::Object exports) {
    auto gc_ns = Napi::Object::New(env);
    exports.Set("GC", gc_ns);
    gc_ns.Set("getStatus", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        dol_GCPadStatus status;
        IPad->getStatus(asS32(info[0]), &status);

        auto res = Napi::Object::New(info.Env());
        res.Set("button", fromU16(info.Env(), status.button));
        res.Set("stickX", fromF32(info.Env(),
                                  (static_cast<float>(status.stickX) - dol_GCPadStatus_MainStickCenterX) /
                                  dol_GCPadStatus_MainStickRadius));
        res.Set("stickY", fromF32(info.Env(),
                                  (static_cast<float>(status.stickY) - dol_GCPadStatus_MainStickCenterY) /
                                  dol_GCPadStatus_MainStickRadius));
        res.Set("substickX", fromF32(info.Env(),
                                     (static_cast<float>(status.substickX) - dol_GCPadStatus_CStickCenterX) /
                                     dol_GCPadStatus_CStickRadius));
        res.Set("substickY", fromF32(info.Env(),
                                     (static_cast<float>(status.substickY) - dol_GCPadStatus_CStickCenterY) /
                                     dol_GCPadStatus_CStickRadius));
        res.Set("triggerLeft", fromF32(info.Env(), static_cast<float>(status.triggerLeft) / 255));
        res.Set("triggerRight", fromF32(info.Env(), static_cast<float>(status.triggerRight) / 255));
        res.Set("analogA", fromF32(info.Env(), static_cast<float>(status.analogA) / 255));
        res.Set("analogB", fromF32(info.Env(), static_cast<float>(status.analogB) / 255));
        res.Set("isConnected", fromBool(info.Env(), status.isConnected));
        return res;
    }));
    gc_ns.Set("rumble", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IPad->rumble(asS32(info[0]), asF64(info[1]));
        return info.Env().Undefined();
    }));
    gc_ns.Set("resetRumble", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IPad->resetRumble(asS32(info[0]));
        return info.Env().Undefined();
    }));
    return exports;
}
