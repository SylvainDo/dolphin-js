#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object State_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("save", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IState->save(asS32(info[0]), true);
        return info.Env().Undefined();
    }));
    exports.Set("load", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IState->load(asS32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("saveAs", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IState->saveAs(asStrUtf8(info[0]).c_str(), true);
        return info.Env().Undefined();
    }));
    exports.Set("loadAs", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IState->loadAs(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("saveToBuffer", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        uint8_t* buffer;
        size_t size;
        IState->saveToBuffer(&buffer, &size);
        auto a = Napi::Buffer<uint8_t>::Copy(info.Env(), buffer, size);
        free(buffer);
        return a;
    }));
    exports.Set("loadFromBuffer", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        auto a = info[0].As<Napi::Uint8Array>();
        IState->loadFromBuffer(a.Data(), a.ByteLength());
        return info.Env().Undefined();
    }));
    return exports;
}
