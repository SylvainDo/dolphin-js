#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;
#include "UICommon_GameFile.hpp"

Napi::Object Util_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("verifyDisc", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        uint8_t sha1[20]{};
        bool goodDump{};
        bool ok = IUtil->verifyDisc(UICommon_GameFile::unwrap(info[0])->iface, sha1, &goodDump);

        auto res = Napi::Object::New(info.Env());
        res.Set("sha1", Napi::Buffer<uint8_t>::Copy(info.Env(), sha1, 20));
        res.Set("goodDump", fromBool(info.Env(), goodDump));
        auto a = Napi::Array::New(info.Env(), 2);
        a.Set(0u, fromBool(info.Env(), ok));
        a.Set(1u, res);
        return a;
    }));
    exports.Set("extractDisc", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        bool ok = IUtil->extractDisc(UICommon_GameFile::unwrap(info[0])->iface, asStrUtf8(info[1]).c_str());
        return fromBool(info.Env(), ok);
    }));
    return exports;
}
