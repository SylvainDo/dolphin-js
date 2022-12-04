#pragma once

class Gui_Q_Action final : public Napi::ObjectWrap<Gui_Q_Action> {
public:
    dol_Gui_Q_Action* iface;

    static Napi::Object initialize(Napi::Env env, Napi::Object exports);
    explicit Gui_Q_Action(const Napi::CallbackInfo& info);
    ~Gui_Q_Action() override;

    static Gui_Q_Action* unwrap(Napi::Value value) {
        return Unwrap(valueAsObject(value));
    }

    static Napi::Value from(dol_Gui_Q_Action* iface);

private:
    Napi::FunctionReference _toggledCallback;
    Napi::FunctionReference _triggeredCallback;

    Napi::Value _setToggledCallback(const Napi::CallbackInfo& info);
    Napi::Value _setTriggeredCallback(const Napi::CallbackInfo& info);
    Napi::Value _isEnabled(const Napi::CallbackInfo& info);
    void _setEnabled(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value _isVisible(const Napi::CallbackInfo& info);
    void _setVisible(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value _isCheckable(const Napi::CallbackInfo& info);
    void _setCheckable(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value _isChecked(const Napi::CallbackInfo& info);
    void _setChecked(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value _setIcon(const Napi::CallbackInfo& info);
    Napi::Value _setText(const Napi::CallbackInfo& info);
    Napi::Value _setShortcut(const Napi::CallbackInfo& info);
};
