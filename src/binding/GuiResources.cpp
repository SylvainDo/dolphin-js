#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object GuiResources_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("init", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiResources->init();
        return info.Env().Undefined();
    }));
    return exports;
}
