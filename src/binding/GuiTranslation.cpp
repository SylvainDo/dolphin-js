#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

Napi::Object GuiTranslation_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("initialize", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGuiTranslation->initialize();
        return info.Env().Undefined();
    }));
    return exports;
}
