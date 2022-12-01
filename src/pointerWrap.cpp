#include "valueConverter.hpp"
using namespace valueConverter;
#include "pointerWrap.hpp"

static Napi::FunctionReference constructor;

Napi::Object PointerWrap::initialize(Napi::Env env, Napi::Object exports) {
    const char* className = "PointerWrap";
    const auto clazz = DefineClass(env, className, {});
    constructor = Napi::Persistent(clazz);
    constructor.SuppressDestruct();
    exports.Set(className, clazz);
    return exports;
}

PointerWrap::PointerWrap(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<PointerWrap>(info),
    value{} {}

Napi::Value PointerWrap::from(void* value) {
    const auto a = constructor.New({});
    PointerWrap::Unwrap(a)->value = value;
    return a;
}
