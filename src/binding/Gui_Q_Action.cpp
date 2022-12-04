#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;
#include "Gui_Q_Action.hpp"

static Napi::FunctionReference constructor;

Napi::Object Gui_Q_Action::initialize(Napi::Env env, Napi::Object exports) {
    const char* className = "Action";
    const auto clazz = DefineClass(env, className, {
        InstanceMethod<&Gui_Q_Action::_setToggledCallback>("setToggledCallback"),
        InstanceMethod<&Gui_Q_Action::_setTriggeredCallback>("setTriggeredCallback"),
        InstanceAccessor<&Gui_Q_Action::_isEnabled, &Gui_Q_Action::_setEnabled>("enabled"),
        InstanceAccessor<&Gui_Q_Action::_isVisible, &Gui_Q_Action::_setVisible>("visible"),
        InstanceAccessor<&Gui_Q_Action::_isCheckable, &Gui_Q_Action::_setCheckable>("checkable"),
        InstanceAccessor<&Gui_Q_Action::_isChecked, &Gui_Q_Action::_setChecked>("checked"),
        InstanceMethod<&Gui_Q_Action::_setIcon>("setIcon"),
        InstanceMethod<&Gui_Q_Action::_setText>("setText"),
        InstanceMethod<&Gui_Q_Action::_setShortcut>("setShortcut")
    });
    constructor = Napi::Persistent(clazz);
    constructor.SuppressDestruct();
    exports.Set(className, clazz);
    return exports;
}

Gui_Q_Action::Gui_Q_Action(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<Gui_Q_Action>(info),
    iface{} {}

Gui_Q_Action::~Gui_Q_Action() {
    iface->destroy(iface);
    free(iface);
}

Napi::Value Gui_Q_Action::from(dol_Gui_Q_Action* iface) {
    const auto a = constructor.New({});
    auto instance = Gui_Q_Action::Unwrap(a);
    instance->Ref();
    instance->iface = iface;
    return a;
}

Napi::Value Gui_Q_Action::_setToggledCallback(const Napi::CallbackInfo& info) {
    _toggledCallback = Napi::Persistent(valueAsFunction(info[0]));
    _toggledCallback.SuppressDestruct();
    iface->setToggledCallback(iface, [](bool checked, void* userdata) {
        auto& func = static_cast<Gui_Q_Action*>(userdata)->_toggledCallback;
        func.Call({ fromBool(func.Env(), checked) });
    }, this);
    return info.Env().Undefined();
}

Napi::Value Gui_Q_Action::_setTriggeredCallback(const Napi::CallbackInfo& info) {
    _triggeredCallback = Napi::Persistent(valueAsFunction(info[0]));
    _triggeredCallback.SuppressDestruct();
    iface->setTriggeredCallback(iface, [](bool checked, void* userdata) {
        auto& func = static_cast<Gui_Q_Action*>(userdata)->_triggeredCallback;
        func.Call({ fromBool(func.Env(), checked) });
    }, this);
    return info.Env().Undefined();
}

Napi::Value Gui_Q_Action::_isEnabled(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isEnabled(iface));
}

void Gui_Q_Action::_setEnabled(const Napi::CallbackInfo& info, const Napi::Value& value) {
    iface->setEnabled(iface, asBool(value));
}

Napi::Value Gui_Q_Action::_isVisible(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isVisible(iface));
}

void Gui_Q_Action::_setVisible(const Napi::CallbackInfo& info, const Napi::Value& value) {
    iface->setVisible(iface, asBool(value));
}

Napi::Value Gui_Q_Action::_isCheckable(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isCheckable(iface));
}

void Gui_Q_Action::_setCheckable(const Napi::CallbackInfo& info, const Napi::Value& value) {
    iface->setCheckable(iface, asBool(value));
}

Napi::Value Gui_Q_Action::_isChecked(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isChecked(iface));
}

void Gui_Q_Action::_setChecked(const Napi::CallbackInfo& info, const Napi::Value& value) {
    iface->setChecked(iface, asBool(value));
}

Napi::Value Gui_Q_Action::_setIcon(const Napi::CallbackInfo& info) {
    iface->setIcon(iface, asCStrUtf8(info[0]));
    return info.Env().Undefined();
}

Napi::Value Gui_Q_Action::_setText(const Napi::CallbackInfo& info) {
    iface->setText(iface, asCStrUtf8(info[0]));
    return info.Env().Undefined();
}

Napi::Value Gui_Q_Action::_setShortcut(const Napi::CallbackInfo& info) {
    iface->setShortcut(iface, asCStrUtf8(info[0]));
    return info.Env().Undefined();
}
