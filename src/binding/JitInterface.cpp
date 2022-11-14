#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object JitInterface_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("clearCache", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IJitInterface->clearCache();
        return info.Env().Undefined();
    }));
    exports.Set("invalidateICache", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IJitInterface->invalidateICache(asU32(info[0]), asU32(info[1]), true);
        return info.Env().Undefined();
    }));
    exports.Set("invalidateICacheLines", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IJitInterface->invalidateICacheLines(asU32(info[0]), asU32(info[1]));
        return info.Env().Undefined();
    }));
    return exports;
}
