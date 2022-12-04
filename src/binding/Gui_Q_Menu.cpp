#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;
#include "Gui_Q_Menu.hpp"
#include "Gui_Q_Action.hpp"

static Napi::FunctionReference constructor;

Napi::Object Gui_Q_Menu::initialize(Napi::Env env, Napi::Object exports) {
    const char* className = "Menu";
    const auto clazz = DefineClass(env, className, {
        InstanceMethod<&Gui_Q_Menu::_addSeparator>("addSeparator"),
        InstanceMethod<&Gui_Q_Menu::_addMenu>("addMenu"),
        InstanceMethod<&Gui_Q_Menu::_addAction>("addAction"),
        InstanceAccessor<&Gui_Q_Menu::_isEnabled, &Gui_Q_Menu::_setEnabled>("enabled"),
        InstanceAccessor<&Gui_Q_Menu::_isVisible, &Gui_Q_Menu::_setVisible>("visible"),
        InstanceMethod<&Gui_Q_Menu::_setIcon>("setIcon"),
        InstanceMethod<&Gui_Q_Menu::_setTitle>("setTitle")
    });
    constructor = Napi::Persistent(clazz);
    constructor.SuppressDestruct();
    exports.Set(className, clazz);
    return exports;
}

Gui_Q_Menu::Gui_Q_Menu(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<Gui_Q_Menu>(info),
    iface{} {}

Gui_Q_Menu::~Gui_Q_Menu() {
    free(iface);
}

Napi::Value Gui_Q_Menu::from(dol_Gui_Q_Menu* iface) {
    const auto a = constructor.New({});
    Gui_Q_Menu::Unwrap(a)->iface = iface;
    return a;
}

Napi::Value Gui_Q_Menu::_addSeparator(const Napi::CallbackInfo& info) {
    return Gui_Q_Action::from(iface->addSeparator(iface));
}

Napi::Value Gui_Q_Menu::_addMenu(const Napi::CallbackInfo& info) {
    return info.Length() > 1 ? Gui_Q_Menu::from(iface->addMenu2(iface, asCStrUtf8(info[0]), asCStrUtf8(info[1])))
                             : Gui_Q_Menu::from(iface->addMenu1(iface, asCStrUtf8(info[0])));
}

Napi::Value Gui_Q_Menu::_addAction(const Napi::CallbackInfo& info) {
    return info.Length() > 1 ? Gui_Q_Action::from(iface->addAction2(iface, asCStrUtf8(info[0]), asCStrUtf8(info[1])))
                             : Gui_Q_Action::from(iface->addAction1(iface, asCStrUtf8(info[0])));
}

Napi::Value Gui_Q_Menu::_isEnabled(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isEnabled(iface));
}

void Gui_Q_Menu::_setEnabled(const Napi::CallbackInfo& info, const Napi::Value& value) {
    iface->setEnabled(iface, asBool(value));
}

Napi::Value Gui_Q_Menu::_isVisible(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isVisible(iface));
}

void Gui_Q_Menu::_setVisible(const Napi::CallbackInfo& info, const Napi::Value& value) {
    iface->setVisible(iface, asBool(value));
}

Napi::Value Gui_Q_Menu::_setIcon(const Napi::CallbackInfo& info) {
    iface->setIcon(iface, asCStrUtf8(info[0]));
    return info.Env().Undefined();
}

Napi::Value Gui_Q_Menu::_setTitle(const Napi::CallbackInfo& info) {
    iface->setTitle(iface, asCStrUtf8(info[0]));
    return info.Env().Undefined();
}
