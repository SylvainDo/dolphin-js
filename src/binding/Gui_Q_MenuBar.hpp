#pragma once

class Gui_Q_MenuBar final : public Napi::ObjectWrap<Gui_Q_MenuBar> {
public:
    dol_Gui_Q_MenuBar* iface;

    static Napi::Object initialize(Napi::Env env, Napi::Object exports);
    explicit Gui_Q_MenuBar(const Napi::CallbackInfo& info);
    ~Gui_Q_MenuBar() override;

    static Gui_Q_MenuBar* unwrap(Napi::Value value) {
        return Unwrap(valueAsObject(value));
    }

    static Napi::Value from(dol_Gui_Q_MenuBar* iface);

private:
    Napi::Value _addMenu(const Napi::CallbackInfo& info);
};
