#include "dol.hpp"
#include "valueConverter.hpp"
using namespace valueConverter;

void dolLoad(const std::string& libraryPath, const std::string& libraryName);
Napi::Object binding_exports(Napi::Env env, Napi::Object exports);

static Napi::Value startup(const Napi::CallbackInfo& info) {
    const auto si = valueAsObject(info[0]);
    const auto libraryPath = asStrUtf8(si.Get("libraryPath"));
    const auto libraryName = asStrUtf8Or(si.Get("libraryName"), "Dolphin.dll");

    try {
        dolLoad(libraryPath, libraryName);
    }
    catch (const std::exception& e) {
        throw Napi::Error::New(info.Env(), e.what());
    }

    IGuiApplication->addLibraryPath(
            (std::filesystem::path(libraryPath) / std::filesystem::path("QtPlugins")).string().c_str());
    IGuiApplication->setExeDirectory(libraryPath.c_str());

    if (si.Has("organizationDomain"))
        IGuiApplication->setOrganizationDomain(asStrUtf8(si.Get("organizationDomain")).c_str());
    else if (si.Has("organizationName"))
        IGuiApplication->setOrganizationName(asStrUtf8(si.Get("organizationName")).c_str());
    else if (si.Has("applicationName"))
        IGuiApplication->setApplicationName(asStrUtf8(si.Get("applicationName")).c_str());
    else if (si.Has("applicationVersion"))
        IGuiApplication->setApplicationVersion(asStrUtf8(si.Get("applicationVersion")).c_str());
    else if (si.Has("applicationDisplayName"))
        IGuiApplication->setApplicationDisplayName(asStrUtf8(si.Get("applicationDisplayName")).c_str());

    return info.Env().Undefined();
}

static Napi::Object initModule(Napi::Env env, Napi::Object exports) {
    exports.Set("startup", Napi::Function::New(env, startup));
    binding_exports(env, exports);
    return exports;
}

NODE_API_MODULE(dolphin_js, initModule)
