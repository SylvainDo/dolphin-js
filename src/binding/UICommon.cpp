#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object UICommon_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("formatSize", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(IUICommon->formatSize(asU64(info[0]), asS32(info[1]))));
    }));
    return exports;
}
