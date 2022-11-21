#pragma once

class UICommon_GameFile final : public Napi::ObjectWrap<UICommon_GameFile> {
public:
    dol_UICommon_GameFile* iface;

    static Napi::Object initialize(Napi::Env env, Napi::Object exports);
    explicit UICommon_GameFile(const Napi::CallbackInfo& info);
    ~UICommon_GameFile() override;

    static UICommon_GameFile* unwrap(Napi::Value value) {
        return Unwrap(valueAsObject(value));
    }

private:
    Napi::Value _isValid(const Napi::CallbackInfo& info);
    Napi::Value _getFilePath(const Napi::CallbackInfo& info);
    Napi::Value _getName(const Napi::CallbackInfo& info);
    Napi::Value _getMaker(const Napi::CallbackInfo& info);
    Napi::Value _getDescription(const Napi::CallbackInfo& info);
    Napi::Value _getLanguages(const Napi::CallbackInfo& info);
    Napi::Value _getInternalName(const Napi::CallbackInfo& info);
    Napi::Value _getGameID(const Napi::CallbackInfo& info);
    Napi::Value _getGameTDBID(const Napi::CallbackInfo& info);
    Napi::Value _getTitleID(const Napi::CallbackInfo& info);
    Napi::Value _getMakerID(const Napi::CallbackInfo& info);
    Napi::Value _getRevision(const Napi::CallbackInfo& info);
    Napi::Value _getDiscNumber(const Napi::CallbackInfo& info);
    Napi::Value _getSyncHash(const Napi::CallbackInfo& info);
    Napi::Value _getWiiFSPath(const Napi::CallbackInfo& info);
    Napi::Value _getRegion(const Napi::CallbackInfo& info);
    Napi::Value _getCountry(const Napi::CallbackInfo& info);
    Napi::Value _getPlatform(const Napi::CallbackInfo& info);
    Napi::Value _getBlobType(const Napi::CallbackInfo& info);
    Napi::Value _getBlockSize(const Napi::CallbackInfo& info);
    Napi::Value _getCompressionMethod(const Napi::CallbackInfo& info);
    Napi::Value _getFileFormatName(const Napi::CallbackInfo& info);
    Napi::Value _getApploaderDate(const Napi::CallbackInfo& info);
    Napi::Value _getFileSize(const Napi::CallbackInfo& info);
    Napi::Value _getVolumeSize(const Napi::CallbackInfo& info);
    Napi::Value _getVolumeSizeType(const Napi::CallbackInfo& info);
    Napi::Value _isDatelDisc(const Napi::CallbackInfo& info);
    Napi::Value _isNKit(const Napi::CallbackInfo& info);
    Napi::Value _isModDescriptor(const Napi::CallbackInfo& info);
    Napi::Value _getBannerImage(const Napi::CallbackInfo& info);
};
