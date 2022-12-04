#include "../dol.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;
#include "Gui_Q_Action.hpp"
#include "Gui_Q_Menu.hpp"
#include "Gui_Q_MenuBar.hpp"

Napi::Object Gui_Q_MenuEtc_exports(Napi::Env env, Napi::Object exports) {
    Gui_Q_Action::initialize(env, exports);
    Gui_Q_Menu::initialize(env, exports);
    Gui_Q_MenuBar::initialize(env, exports);
    return exports;
}
