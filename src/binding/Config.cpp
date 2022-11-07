#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

#include <fmt/format.h>

static void* findProp(std::string_view expr, bool* isBaseLayer, const Napi::CallbackInfo& args, int* argsOffset) {
    *isBaseLayer = expr[0] == '-';
    if (*isBaseLayer) expr = expr.substr(1);
    const auto isCall = expr[0] == '@';

    if (isCall) {
        expr = expr.substr(1);
        *argsOffset = 1;

        if (expr == "MemcardPath")
            return IConfig->getInfoForMemcardPath(static_cast<dol_ExpansionInterface_Slot>(asS32(args[1])));
        else if (expr == "AGPCartPath")
            return IConfig->getInfoForAGPCartPath(static_cast<dol_ExpansionInterface_Slot>(asS32(args[1])));
        else if (expr == "GCIPathOverride")
            return IConfig->getInfoForGCIPathOverride(static_cast<dol_ExpansionInterface_Slot>(asS32(args[1])));
        else if (expr == "EXIDevice")
            return IConfig->getInfoForEXIDevice(static_cast<dol_ExpansionInterface_Slot>(asS32(args[1])));
        else if (expr == "SIDevice")
            return IConfig->getInfoForSIDevice(asS32(args[1]));
        else if (expr == "AdapterRumble")
            return IConfig->getInfoForAdapterRumble(asS32(args[1]));
        else if (expr == "SimulateKonga")
            return IConfig->getInfoForSimulateKonga(asS32(args[1]));
        else if (expr == "WiimoteSource")
            return IConfig->getInfoForWiimoteSource(asS32(args[1]));
    }
    else {
        *argsOffset = 0;

        const auto comma = expr.find_first_of(',');
        const auto period = expr.find_first_of('.');

        if (comma == std::string_view::npos && period == std::string_view::npos) {
            const auto name = std::string(expr);
            return IConfig->findInfo1(name.c_str());
        }
        else if (comma != std::string_view::npos && period != std::string_view::npos) {
            const auto system = expr.substr(0, comma);
            const auto section = std::string(expr.substr(comma + 1, period - comma - 1));
            const auto key = std::string(expr.substr(period + 1));
            dol_Config_System configSystem;
            if (system == "Main") configSystem = dol_Config_System_Main;
            else if (system == "SYSCONF") configSystem = dol_Config_System_SYSCONF;
            else if (system == "GCPad") configSystem = dol_Config_System_GCPad;
            else if (system == "WiiPad") configSystem = dol_Config_System_WiiPad;
            else if (system == "GCKeyboard") configSystem = dol_Config_System_GCKeyboard;
            else if (system == "GFX") configSystem = dol_Config_System_GFX;
            else if (system == "Logger") configSystem = dol_Config_System_Logger;
            else if (system == "Debugger") configSystem = dol_Config_System_Debugger;
            else if (system == "DualShockUDPClient") configSystem = dol_Config_System_DualShockUDPClient;
            else if (system == "FreeLook") configSystem = dol_Config_System_FreeLook;
            else if (system == "Session") configSystem = dol_Config_System_Session;
            else return nullptr;
            return IConfig->findInfo2(configSystem, section.c_str(), key.c_str());
        }
        else if (period != std::string_view::npos) {
            const auto section = std::string(expr.substr(0, period));
            const auto key = std::string(expr.substr(period + 1));
            return IConfig->findInfo2(static_cast<dol_Config_System>(-1), section.c_str(), key.c_str());
        }
    }
    return nullptr;
}

Napi::Object Config_exports(Napi::Env env, Napi::Object exports) {
#define getter(_1, _2, _3) \
    exports.Set("get" #_1, Napi::Function::New(env, [](const Napi::CallbackInfo& info) { \
        bool isBaseLayer; \
        int argsOffset; \
        const auto propName = asStrUtf8(info[0]); \
        const auto prop = findProp(propName, &isBaseLayer, info, &argsOffset); \
        if (!prop) \
            throw Napi::Error::New(info.Env(), fmt::format("invalid property: '{}'", propName)); \
        return from##_2(info.Env(), IConfig->getInfo##_3(prop, isBaseLayer)); \
    }));
    getter(Int, S32, 1)
    getter(Bool, Bool, 1)
    getter(Float, F32, 3)
    getter(Uint16, U16, 4)
    getter(Uint32, U32, 5)
#undef getter

#define setter(_1, _2, _3) \
    exports.Set("set" #_1, Napi::Function::New(env, [](const Napi::CallbackInfo& info) { \
        bool isBaseLayer; \
        int argsOffset; \
        const auto propName = asStrUtf8(info[0]); \
        const auto prop = findProp(propName, &isBaseLayer, info, &argsOffset); \
        if (!prop) \
            throw Napi::Error::New(info.Env(), fmt::format("invalid property: '{}'", propName)); \
        IConfig->setInfo##_3(prop, as##_2(info[argsOffset + 1]), isBaseLayer); \
        return info.Env().Undefined(); \
    }));
    setter(Int, S32, 1)
    setter(Bool, Bool, 1)
    setter(Float, F32, 3)
    setter(Uint16, U16, 4)
    setter(Uint32, U32, 5)
#undef setter

    exports.Set("getString", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        bool isBaseLayer;
        int argsOffset;
        const auto propName = asStrUtf8(info[0]);
        const auto prop = findProp(propName, &isBaseLayer, info, &argsOffset);
        if (!prop)
            throw Napi::Error::New(info.Env(), fmt::format("invalid property: '{}'", propName));
        return fromStrUtf8(info.Env(), util::copyString(IConfig->getInfo2(prop, isBaseLayer)));
    }));
    exports.Set("setString", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        bool isBaseLayer;
        int argsOffset;
        const auto propName = asStrUtf8(info[0]);
        const auto prop = findProp(propName, &isBaseLayer, info, &argsOffset);
        if (!prop)
            throw Napi::Error::New(info.Env(), fmt::format("invalid property: '{}'", propName));
        IConfig->setInfo2(prop, asStrUtf8(info[argsOffset + 1]).c_str(), isBaseLayer);
        return info.Env().Undefined();
    }));
    return exports;
}
