#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object AddressSpace_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("isValidAddress", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        const auto address_space = static_cast<dol_AddressSpace_Type>(asS32(info[0]));
        return fromBool(info.Env(), IAddressSpace_Accessors->isValidAddress(address_space, asU32(info[1])));
    }));
    exports.Set("get", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        const auto address_space = static_cast<dol_AddressSpace_Type>(asS32(info[0]));
        return Napi::ArrayBuffer::New(info.Env(),
                                      const_cast<uint8_t*>(IAddressSpace_Accessors->begin(address_space)),
                                      IAddressSpace_Accessors->end(address_space) -
                                      IAddressSpace_Accessors->begin(address_space));
    }));
    exports.Set("slice", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        const auto address_space = static_cast<dol_AddressSpace_Type>(asS32(info[0]));
        const auto begin = IAddressSpace_Accessors->begin(address_space) + asS32(info[1]);
        const auto end = info[2].IsUndefined() ? IAddressSpace_Accessors->end(address_space) :
                         IAddressSpace_Accessors->begin(address_space) + asS32(info[2]);
        return Napi::ArrayBuffer::New(info.Env(), const_cast<uint8_t*>(begin), end - begin);
    }));
    exports.Set("search", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        const auto address_space = static_cast<dol_AddressSpace_Type>(asS32(info[0]));
        const auto needle = info[2].As<Napi::Uint8Array>();
        uint32_t result;
        if (IAddressSpace_Accessors->search(address_space, asU32(info[1]), needle.Data(), needle.ByteLength(),
                                            asBoolOr(info[3], true), &result))
            return fromU32(info.Env(), result);
        return info.Env().Undefined();
    }));
    return exports;
}
