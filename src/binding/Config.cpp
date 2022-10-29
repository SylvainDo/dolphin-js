#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

#include <vector>

static void* findProp(std::string_view expr, bool* isBaseLayer, const Napi::CallbackInfo& args, int* argsOffset) {
    *isBaseLayer = expr[0] == '-';
    if (*isBaseLayer) expr = expr.substr(1);
    const auto isCall = expr[0] == '@';

    if (isCall) {
        expr = expr.substr(1);
        *argsOffset = 1;

        if (expr == "MemcardPath")
            return IConfig->getInfoForMemcardPath(static_cast<dolExpansionInterfaceSlot>(asS32(args[1])));
        else if (expr == "AGPCartPath")
            return IConfig->getInfoForAGPCartPath(static_cast<dolExpansionInterfaceSlot>(asS32(args[1])));
        else if (expr == "GCIPathOverride")
            return IConfig->getInfoForGCIPathOverride(static_cast<dolExpansionInterfaceSlot>(asS32(args[1])));
        else if (expr == "EXIDevice")
            return IConfig->getInfoForEXIDevice(static_cast<dolExpansionInterfaceSlot>(asS32(args[1])));
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
            dolConfigSystem configSystem;
            if (system == "Main") configSystem = dolConfigSystem_Main;
            else if (system == "SYSCONF") configSystem = dolConfigSystem_SYSCONF;
            else if (system == "GCPad") configSystem = dolConfigSystem_GCPad;
            else if (system == "WiiPad") configSystem = dolConfigSystem_WiiPad;
            else if (system == "GCKeyboard") configSystem = dolConfigSystem_GCKeyboard;
            else if (system == "GFX") configSystem = dolConfigSystem_GFX;
            else if (system == "Logger") configSystem = dolConfigSystem_Logger;
            else if (system == "Debugger") configSystem = dolConfigSystem_Debugger;
            else if (system == "DualShockUDPClient") configSystem = dolConfigSystem_DualShockUDPClient;
            else if (system == "FreeLook") configSystem = dolConfigSystem_FreeLook;
            else if (system == "Session") configSystem = dolConfigSystem_Session;
            else return nullptr;
            return IConfig->findInfo2(configSystem, section.c_str(), key.c_str());
        }
        else if (period != std::string_view::npos) {
            const auto section = std::string(expr.substr(0, period));
            const auto key = std::string(expr.substr(period + 1));
            return IConfig->findInfo2(static_cast<dolConfigSystem>(-1), section.c_str(), key.c_str());
        }
    }
    return nullptr;
}

Napi::Object Config_exports(Napi::Env env, Napi::Object exports) {
#define getter(_1, _2, _3) \
    exports.Set("get" #_1, Napi::Function::New(env, [](const Napi::CallbackInfo& info) { \
        bool isBaseLayer; \
        int argsOffset; \
        const auto prop = findProp(asStrUtf8(info[0]), &isBaseLayer, info, &argsOffset); \
        if (!prop) throw Napi::Error::New(info.Env(), "invalid property"); \
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
        const auto prop = findProp(asStrUtf8(info[0]), &isBaseLayer, info, &argsOffset); \
        if (!prop) throw Napi::Error::New(info.Env(), "invalid property"); \
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
        const auto prop = findProp(asStrUtf8(info[0]), &isBaseLayer, info, &argsOffset);
        if (!prop) throw Napi::Error::New(info.Env(), "invalid property");
        return fromStrUtf8(info.Env(), util::copyString(IConfig->getInfo2(prop, isBaseLayer)));
    }));
    exports.Set("setString", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        bool isBaseLayer;
        int argsOffset;
        const auto prop = findProp(asStrUtf8(info[0]), &isBaseLayer, info, &argsOffset);
        if (!prop) throw Napi::Error::New(info.Env(), "invalid property");
        IConfig->setInfo2(prop, asStrUtf8(info[argsOffset + 1]).c_str(), isBaseLayer);
        return info.Env().Undefined();
    }));

    exports.Set("getDefaultLanguage", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IConfig->getDefaultLanguage());
    }));
    exports.Set("getOptionalDefaultCountry", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        uint8_t defaultCountry;
        return IConfig->getOptionalDefaultCountry(&defaultCountry) ?
               fromU8(info.Env(), defaultCountry) : info.Env().Undefined();
    }));
    exports.Set("getDefaultCountry", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU8(info.Env(), IConfig->getDefaultCountry());
    }));
    exports.Set("getDefaultRegion", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IConfig->getDefaultRegion());
    }));
    exports.Set("getGPUDeterminismMode", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IConfig->getGPUDeterminismMode());
    }));
    exports.Set("shouldUseDPL2Decoder", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IConfig->shouldUseDPL2Decoder());
    }));
    exports.Set("getIsoPaths", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        int numPaths;
        auto paths = IConfig->getIsoPaths(&numPaths);
        auto v = Napi::Array::New(info.Env(), numPaths);
        for (int i{}; i < numPaths; ++i)
            v.Set(i, fromStrUtf8(info.Env(), util::copyString(paths[i])));
        free(paths);
        return v;
    }));
    exports.Set("setIsoPaths", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        const auto a = valueAsArray(info[0]);
        const auto length = a.Length();
        std::vector<std::string> temp1(length);
        std::vector<const char*> temp2(length);
        for (int i{}; i < length; ++i) {
            temp1[i] = asStrUtf8(a.Get(i));
            temp2[i] = temp1[i].c_str();
        }
        IConfig->setIsoPaths(temp2.data(), static_cast<int>(temp2.size()));
        return info.Env().Undefined();
    }));
    exports.Set("getUSBDeviceWhitelist", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        uint16_t* devices_first;
        uint16_t* devices_second;
        int numDevices;
        IConfig->getUSBDeviceWhitelist(&devices_first, &devices_second, &numDevices);
        auto v = Napi::Array::New(info.Env(), numDevices);
        for (int i{}; i < numDevices; ++i) {
            auto a = Napi::Array::New(info.Env());
            a.Set(0u, fromU16(info.Env(), devices_first[i]));
            a.Set(1u, fromU16(info.Env(), devices_second[i]));
            v.Set(i, a);
        }
        free(devices_first);
        free(devices_second);
        return v;
    }));
    exports.Set("setUSBDeviceWhitelist", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        std::vector<uint16_t> devices_first;
        std::vector<uint16_t> devices_second;
        auto v = valueAsArray(info[0]);
        for (int i{}; i < v.Length(); ++i) {
            auto a = valueAsArray(v.Get(i));
            devices_first.push_back(asU16(a.Get(0u)));
            devices_second.push_back(asU16(a.Get(1u)));
        }
        IConfig->setUSBDeviceWhitelist(devices_first.data(), devices_second.data(),
                                       static_cast<int>(devices_first.size()));
        return info.Env().Undefined();
    }));
    exports.Set("toGameCubeRegion", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IConfig->toGameCubeRegion(static_cast<dolDiscIORegion>(asS32(info[0]))));
    }));
    exports.Set("getDirectoryForRegion", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(),
                           util::copyString(
                                   IConfig->getDirectoryForRegion(static_cast<dolDiscIORegion>(asS32(info[0])))));
    }));
    exports.Set("getBootROMPath", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(IConfig->getBootROMPath(asStrUtf8(info[0]).c_str())));
    }));
    exports.Set("getMemcardPath", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        dolDiscIORegion region;
        if (info[0].IsString()) {
            if (!info[2].IsUndefined()) region = static_cast<dolDiscIORegion>(asS32(info[2]));
            return fromStrUtf8(info.Env(), util::copyString(IConfig->getMemcardPath2(
                    asStrUtf8(info[0]).c_str(),
                    static_cast<dolExpansionInterfaceSlot>(asS32(info[1])),
                    info[2].IsUndefined() ? nullptr : &region,
                    asU16(info[3]))));
        }
        else {
            if (!info[1].IsUndefined()) region = static_cast<dolDiscIORegion>(asS32(info[1]));
            return fromStrUtf8(info.Env(), util::copyString(IConfig->getMemcardPath1(
                    static_cast<dolExpansionInterfaceSlot>(asS32(info[0])),
                    info[1].IsUndefined() ? nullptr : &region,
                    asU16(info[2]))));
        }
    }));
    exports.Set("isDefaultMemcardPathConfigured", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromBool(info.Env(), IConfig->isDefaultMemcardPathConfigured(
                static_cast<dolExpansionInterfaceSlot>(asS32(info[0]))));
    }));
    return exports;
}
