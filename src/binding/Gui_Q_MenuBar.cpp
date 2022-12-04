#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;
#include "Gui_Q_MenuBar.hpp"
#include "Gui_Q_Menu.hpp"

static Napi::FunctionReference constructor;

Napi::Object Gui_Q_MenuBar::initialize(Napi::Env env, Napi::Object exports) {
    const char* className = "MenuBar";
    const auto clazz = DefineClass(env, className, {
        InstanceMethod<&Gui_Q_MenuBar::_addMenu>("addMenu")
    });
    constructor = Napi::Persistent(clazz);
    constructor.SuppressDestruct();
    exports.Set(className, clazz);
    return exports;
}

Gui_Q_MenuBar::Gui_Q_MenuBar(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<Gui_Q_MenuBar>(info),
    iface{} {}

Gui_Q_MenuBar::~Gui_Q_MenuBar() {
    free(iface);
}

Napi::Value Gui_Q_MenuBar::from(dol_Gui_Q_MenuBar* iface) {
    const auto a = constructor.New({});
    Gui_Q_MenuBar::Unwrap(a)->iface = iface;
    return a;
}

Napi::Value Gui_Q_MenuBar::_addMenu(const Napi::CallbackInfo& info) {
    return Gui_Q_Menu::from(iface->addMenu(iface, asCStrUtf8(info[0])));
}
