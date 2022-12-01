#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;
#include "../pointerWrap.hpp"

namespace {

void* getParentOrNull(const Napi::Value& value) {
    return value.IsUndefined() ? nullptr : PointerWrap::unwrap(value)->value;
}

dol_Gui_Q_Color toColor(const Napi::Value& value) {
    const auto a = valueAsObject(value);
    return {
        .r = asS32(a.Get("r")),
        .g = asS32(a.Get("g")),
        .b = asS32(a.Get("b")),
        .a = asS32(a.Get("a"))
    };
}

Napi::Value fromColor(Napi::Env env, dol_Gui_Q_Color color) {
    auto a = Napi::Object::New(env);
    a.Set("r", fromS32(env, color.r));
    a.Set("g", fromS32(env, color.g));
    a.Set("b", fromS32(env, color.b));
    a.Set("a", fromS32(env, color.a));
    return a;
}

constexpr dol_Gui_Q_Color White{ 255, 255, 255, 255 };

}

Napi::Object Gui_Q_CommonDialogs_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("about", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IGui_Q_CommonDialogs->about(getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]));
        return info.Env().Undefined();
    }));
    exports.Set("critical", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGui_Q_CommonDialogs->critical(
            getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]), asS32Or(info[3], 0x00000400),
            asS32Or(info[4], 0x00000000)));
    }));
    exports.Set("information", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGui_Q_CommonDialogs->information(
            getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]), asS32Or(info[3], 0x00000400),
            asS32Or(info[4], 0x00000000)));
    }));
    exports.Set("question", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGui_Q_CommonDialogs->question(
            getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]),
            asS32Or(info[3], 0x00004000 | 0x00010000),
            asS32Or(info[4], 0x00000000)));
    }));
    exports.Set("warning", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), IGui_Q_CommonDialogs->warning(
            getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]), asS32Or(info[3], 0x00000400),
            asS32Or(info[4], 0x00000000)));
    }));
    exports.Set("getColor", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromColor(info.Env(), IGui_Q_CommonDialogs->getColor(
            info[2].IsUndefined() ? White : toColor(info[2]), getParentOrNull(info[0]), asCStrUtf8Or(info[1], ""),
            asS32Or(info[3], 0)));
    }));
    exports.Set("getDouble", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        bool ok;
        auto a = Napi::Array::New(info.Env());
        a.Set(0u, fromF64(info.Env(), IGui_Q_CommonDialogs->getDouble(
            getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]), asF64Or(info[3], 0),
            asF64Or(info[4], -2147483647), asF64Or(info[5], 2147483647), asS32Or(info[6], 1),
            &ok, asF64Or(info[7], 1))));
        a.Set(1u, fromBool(info.Env(), ok));
        return a;
    }));
    exports.Set("getInt", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        bool ok;
        auto a = Napi::Array::New(info.Env());
        a.Set(0u, fromS32(info.Env(), IGui_Q_CommonDialogs->getInt(
            getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]), asS32Or(info[3], 0),
            asS32Or(info[4], -2147483647), asS32Or(info[5], 2147483647), asS32Or(info[6], 1),
            &ok)));
        a.Set(1u, fromBool(info.Env(), ok));
        return a;
    }));
    exports.Set("getItem", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        const auto items = valueAsArray(info[3]);
        std::vector<std::string> vItems(items.Length());
        std::vector<const char*> vItemsTmp(items.Length());
        for (size_t i{}; i < vItems.size(); ++i) {
            vItems[i] = asStrUtf8(items.Get(i));
            vItemsTmp[i] = vItems[i].c_str();
        }

        bool ok;
        auto a = Napi::Array::New(info.Env());
        a.Set(0u, fromStrUtf8(info.Env(), util::copyString(IGui_Q_CommonDialogs->getItem(
            getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]), vItemsTmp.data(),
            static_cast<int>(vItemsTmp.size()), asS32Or(info[4], 0), asBoolOr(info[5], true),
            &ok))));
        a.Set(1u, fromBool(info.Env(), ok));
        return a;
    }));
    exports.Set("getMultiLineText", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        bool ok;
        auto a = Napi::Array::New(info.Env());
        a.Set(0u, fromStrUtf8(info.Env(), util::copyString(IGui_Q_CommonDialogs->getMultiLineText(
            getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]), asCStrUtf8Or(info[3], ""), &ok))));
        a.Set(1u, fromBool(info.Env(), ok));
        return a;
    }));
    exports.Set("getText", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        bool ok;
        auto a = Napi::Array::New(info.Env());
        a.Set(0u, fromStrUtf8(info.Env(), util::copyString(IGui_Q_CommonDialogs->getText(
            getParentOrNull(info[0]), asCStrUtf8(info[1]), asCStrUtf8(info[2]), asS32Or(info[3], 0),
            asCStrUtf8Or(info[4], ""), &ok))));
        a.Set(1u, fromBool(info.Env(), ok));
        return a;
    }));
    exports.Set("getExistingDirectory", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(IGui_Q_CommonDialogs->getExistingDirectory(
            getParentOrNull(info[0]), asCStrUtf8Or(info[1], ""), asCStrUtf8Or(info[2], ""),
            asS32Or(info[3], 0x00000001))));
    }));
    exports.Set("getOpenFileName", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        auto a = Napi::Array::New(info.Env());
        char* selectedFilter;
        a.Set(0u, fromStrUtf8(info.Env(), util::copyString(IGui_Q_CommonDialogs->getOpenFileName(
            getParentOrNull(info[0]), asCStrUtf8Or(info[1], ""), asCStrUtf8Or(info[2], ""), asCStrUtf8Or(info[3], ""),
            &selectedFilter, asS32Or(info[4], 0)))));
        a.Set(1u, fromStrUtf8(info.Env(), selectedFilter));
        free(selectedFilter);
        return a;
    }));
    exports.Set("getOpenFileNames", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        auto a = Napi::Array::New(info.Env());
        char* selectedFilter;
        int numPaths;
        auto res = IGui_Q_CommonDialogs->getOpenFileNames(
            getParentOrNull(info[0]), asCStrUtf8Or(info[1], ""), asCStrUtf8Or(info[2], ""), asCStrUtf8Or(info[3], ""),
            &selectedFilter, asS32Or(info[4], 0), &numPaths);
        auto paths = Napi::Array::New(info.Env(), numPaths);
        for (int i{}; i < numPaths; ++i)
            paths.Set(i, fromStrUtf8(info.Env(), util::copyString(res[i])));
        a.Set(0u, paths);
        a.Set(1u, fromStrUtf8(info.Env(), selectedFilter));
        free(selectedFilter);
        return a;
    }));
    exports.Set("getSaveFileName", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        auto a = Napi::Array::New(info.Env());
        char* selectedFilter;
        a.Set(0u, fromStrUtf8(info.Env(), util::copyString(IGui_Q_CommonDialogs->getSaveFileName(
            getParentOrNull(info[0]), asCStrUtf8Or(info[1], ""), asCStrUtf8Or(info[2], ""), asCStrUtf8Or(info[3], ""),
            &selectedFilter, asS32Or(info[4], 0)))));
        a.Set(1u, fromStrUtf8(info.Env(), selectedFilter));
        free(selectedFilter);
        return a;
    }));
    return exports;
}
