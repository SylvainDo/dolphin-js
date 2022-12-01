#pragma once

struct PointerWrap final : Napi::ObjectWrap<PointerWrap> {
    void* value;

    static Napi::Object initialize(Napi::Env env, Napi::Object exports);
    explicit PointerWrap(const Napi::CallbackInfo& info);

    static PointerWrap* unwrap(Napi::Value value) {
        return Unwrap(valueAsObject(value));
    }

    static Napi::Value from(void* value);
};
