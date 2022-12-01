#include "dol.hpp"
#include "util.hpp"
#include "valueConverter.hpp"
using namespace valueConverter;
#include "pointerWrap.hpp"

void dolLoad(const std::string& libraryPath, const std::string& libraryName);
Napi::Object binding_exports(Napi::Env env, Napi::Object exports);

static Napi::Object initModule(Napi::Env env, Napi::Object exports) {
    PointerWrap::initialize(env, exports);
    auto dolphinNs = Napi::Object::New(env);
    dolphinNs.Set("loadLibrary", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        const auto _info = valueAsObject(info[0]);
        const auto libraryPath = asStrUtf8(_info.Get("libraryPath"));
#ifdef _WIN32
        const auto libraryName = asStrUtf8Or(_info.Get("libraryName"), "Dolphin.dll");
#else
        const auto libraryName = asStrUtf8Or(_info.Get("libraryName"), "libdolphin-emu.so");
#endif

        try {
            dolLoad(libraryPath, libraryName);
        }
        catch (const std::exception& e) {
            throw Napi::Error::New(info.Env(), e.what());
        }

        IGui_Application->addLibraryPath(
                (std::filesystem::path(libraryPath) / std::filesystem::path("QtPlugins")).string().c_str());
        IGui_Application->setExeDirectory(libraryPath.c_str());

        return info.Env().Undefined();
    }));
    dolphinNs.Set("startup", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        const auto _info = valueAsObject(info[0]);

        if (_info.Has("organizationDomain"))
            IGui_Application->setOrganizationDomain(asStrUtf8(_info.Get("organizationDomain")).c_str());
        else if (_info.Has("organizationName"))
            IGui_Application->setOrganizationName(asStrUtf8(_info.Get("organizationName")).c_str());
        else if (_info.Has("applicationName"))
            IGui_Application->setApplicationName(asStrUtf8(_info.Get("applicationName")).c_str());
        else if (_info.Has("applicationVersion"))
            IGui_Application->setApplicationVersion(asStrUtf8(_info.Get("applicationVersion")).c_str());
        else if (_info.Has("applicationDisplayName"))
            IGui_Application->setApplicationDisplayName(asStrUtf8(_info.Get("applicationDisplayName")).c_str());

        IGui_Host->declareAsHostThread();
        IGui_Application->init();
        IUICommon->setUserDirectory(asStrUtf8Or(_info.Get("userDirectoryPath"), "").c_str());
        IUICommon->createDirectories();
        IUICommon->init();

        if (!info[1].IsUndefined())
            valueAsFunction(info[1]).Call({});

        IGui_Resources->init();
        IGui_Settings->setBatchModeEnabled(false);
        IGui_Translation->initialize();
        IGui_MainWindow->init();
        IGui_Settings->setCurrentUserStyle(util::copyString(IGui_Settings->getCurrentUserStyle()).c_str());
        IGui_Settings->setDebugModeEnabled(false);
        IConfig->setInfo1(IConfig->findInfo1("MAIN_ANALYTICS_PERMISSION_ASKED"), true, true);
        IGui_Settings->setAnalyticsEnabled(false);
        IDolphinAnalytics->reloadConfig();
        IState->enableCompression(true);

        return info.Env().Undefined();
    }));
    dolphinNs.Set("shutdown", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_MainWindow->shutdown();
        ICore->shutdown();
        IUICommon->shutdown();
        IGui_Host->deleteLater();
        IGui_Application->shutdown();

        return info.Env().Undefined();
    }));
    dolphinNs.Set("processOne", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Application->processEvents3();
        ICore->hostDispatchJobs();

        return info.Env().Undefined();
    }));
    dolphinNs.Set("enableFrameHandler", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        ICore->setFrameHandlerEnabled(asBool(info[0]));
        return info.Env().Undefined();
    }));
    dolphinNs.Set("handleFrame", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        if (ICore->getFrameHandlerToken()) {
            valueAsFunction(info[0]).Call({});
            ICore->setFrameHandlerToken(false);
            return fromBool(info.Env(), true);
        }
        return fromBool(info.Env(), false);
    }));
    exports.Set("Dolphin", dolphinNs);
    binding_exports(env, exports);
    return exports;
}

NODE_API_MODULE(dolphin_js, initModule)
