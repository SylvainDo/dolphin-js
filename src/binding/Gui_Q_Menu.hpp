#pragma once

class Gui_Q_Menu final : public Napi::ObjectWrap<Gui_Q_Menu> {
public:
    dol_Gui_Q_Menu* iface;

    static Napi::Object initialize(Napi::Env env, Napi::Object exports);
    explicit Gui_Q_Menu(const Napi::CallbackInfo& info);
    ~Gui_Q_Menu() override;

    static Gui_Q_Menu* unwrap(Napi::Value value) {
        return Unwrap(valueAsObject(value));
    }

    static Napi::Value from(dol_Gui_Q_Menu* iface);

private:
    Napi::Value _addSeparator(const Napi::CallbackInfo& info);
    Napi::Value _addMenu(const Napi::CallbackInfo& info);
    Napi::Value _addAction(const Napi::CallbackInfo& info);
    Napi::Value _isEnabled(const Napi::CallbackInfo& info);
    void _setEnabled(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value _isVisible(const Napi::CallbackInfo& info);
    void _setVisible(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value _setIcon(const Napi::CallbackInfo& info);
    Napi::Value _setTitle(const Napi::CallbackInfo& info);
};
