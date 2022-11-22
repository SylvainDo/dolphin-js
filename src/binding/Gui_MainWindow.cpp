#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

namespace ResetCallback {

Napi::FunctionReference reference;

void callback(void*) {
    if (reference)
        reference.Call({});
}

}

Napi::Object Gui_MainWindow_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("show", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_MainWindow->show();
        return info.Env().Undefined();
    }));
    exports.Set("startGame", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_MainWindow->startGame1(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
    exports.Set("setResetCallback", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        ResetCallback::reference = Napi::Persistent(valueAsFunction(info[0]));
        ResetCallback::reference.SuppressDestruct();
        IGui_MainWindow->setResetCallback(ResetCallback::callback, nullptr);
        return info.Env().Undefined();
    }));
    return exports;
}
