#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;
#include "../pointerWrap.hpp"
#include "Gui_Q_Menu.hpp"
#include "Gui_Q_MenuBar.hpp"

namespace ResetCallback {

Napi::FunctionReference reference;

void callback(void*) {
    if (reference)
        reference.Call({});
}

}

namespace EmulationStateChanged {

Napi::FunctionReference reference;

void callback(dol_Core_State state, void*) {
    if (reference)
        reference.Call({ fromS32(reference.Env(), state) });
}

}

Napi::Object Gui_MainWindow_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("setIcon", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_MainWindow->setIcon(asStrUtf8(info[0]).c_str());
        return info.Env().Undefined();
    }));
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
    exports.Set("setEmulationStateChangedCallback", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        EmulationStateChanged::reference = Napi::Persistent(valueAsFunction(info[0]));
        EmulationStateChanged::reference.SuppressDestruct();
        IGui_MainWindow->setEmulationStateChangedCallback(EmulationStateChanged::callback, nullptr);
        return info.Env().Undefined();
    }));
    exports.Set("close", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_MainWindow->close();
        return info.Env().Undefined();
    }));
    exports.Set("asWidget", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return PointerWrap::from(IGui_MainWindow->asWidget());
    }));
    exports.Set("getMenuBar", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return Gui_Q_MenuBar::from(IGui_MainWindow->getMenuBar());
    }));
    exports.Set("findMenu", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        const auto menu = IGui_MainWindow->findMenu(asCStrUtf8(info[0]));
        return menu ? Gui_Q_Menu::from(menu) : info.Env().Undefined();
    }));
    return exports;
}
