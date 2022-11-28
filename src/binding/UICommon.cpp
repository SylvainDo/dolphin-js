#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;
#include "UICommon_GameFile.hpp"

Napi::Object UICommon_exports(Napi::Env env, Napi::Object exports) {
    UICommon_GameFile::initialize(env, exports);
    exports.Set("createDirectories", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IUICommon->setUserDirectory(asStrUtf8(info[0]).c_str());
        IUICommon->createDirectories();
        return info.Env().Undefined();
    }));
    exports.Set("formatSize", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(
                IUICommon->formatSize(asU64(info[0]), asS32(info[1]))));
    }));
    return exports;
}
