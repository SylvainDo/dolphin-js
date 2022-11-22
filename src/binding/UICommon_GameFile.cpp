#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;
#include "UICommon_GameFile.hpp"

static Napi::FunctionReference constructor;

Napi::Object UICommon_GameFile::initialize(Napi::Env env, Napi::Object exports) {
    const char* className = "GameFile";
    const auto clazz = DefineClass(env, className, {
            InstanceAccessor<&UICommon_GameFile::_isValid>("isValid"),
            InstanceAccessor<&UICommon_GameFile::_getFilePath>("filePath"),
            InstanceAccessor<&UICommon_GameFile::_getName>("name"),
            InstanceAccessor<&UICommon_GameFile::_getMaker>("maker"),
            InstanceAccessor<&UICommon_GameFile::_getDescription>("description"),
            InstanceAccessor<&UICommon_GameFile::_getLanguages>("languages"),
            InstanceAccessor<&UICommon_GameFile::_getInternalName>("internalName"),
            InstanceAccessor<&UICommon_GameFile::_getGameID>("gameID"),
            InstanceAccessor<&UICommon_GameFile::_getGameTDBID>("gameTDBID"),
            InstanceAccessor<&UICommon_GameFile::_getTitleID>("titleID"),
            InstanceAccessor<&UICommon_GameFile::_getMakerID>("makerID"),
            InstanceAccessor<&UICommon_GameFile::_getRevision>("revision"),
            InstanceAccessor<&UICommon_GameFile::_getDiscNumber>("discNumber"),
            InstanceAccessor<&UICommon_GameFile::_getSyncHash>("syncHash"),
            InstanceAccessor<&UICommon_GameFile::_getWiiFSPath>("wiiFSPath"),
            InstanceAccessor<&UICommon_GameFile::_getRegion>("region"),
            InstanceAccessor<&UICommon_GameFile::_getCountry>("country"),
            InstanceAccessor<&UICommon_GameFile::_getPlatform>("platform"),
            InstanceAccessor<&UICommon_GameFile::_getBlobType>("blobType"),
            InstanceAccessor<&UICommon_GameFile::_getBlockSize>("blockSize"),
            InstanceAccessor<&UICommon_GameFile::_getCompressionMethod>("compressionMethod"),
            InstanceAccessor<&UICommon_GameFile::_getFileFormatName>("fileFormatName"),
            InstanceAccessor<&UICommon_GameFile::_getApploaderDate>("apploaderDate"),
            InstanceAccessor<&UICommon_GameFile::_getFileSize>("fileSize"),
            InstanceAccessor<&UICommon_GameFile::_getVolumeSize>("volumeSize"),
            InstanceAccessor<&UICommon_GameFile::_getVolumeSizeType>("volumeSizeType"),
            InstanceAccessor<&UICommon_GameFile::_isDatelDisc>("isDatelDisc"),
            InstanceAccessor<&UICommon_GameFile::_isNKit>("isNKit"),
            InstanceAccessor<&UICommon_GameFile::_isModDescriptor>("isModDescriptor"),
            InstanceAccessor<&UICommon_GameFile::_getBannerImage>("bannerImage"),
            InstanceAccessor<&UICommon_GameFile::_getLocalIniPath>("localIniPath")
    });
    constructor = Napi::Persistent(clazz);
    constructor.SuppressDestruct();
    exports.Set(className, clazz);
    return exports;
}

UICommon_GameFile::UICommon_GameFile(const Napi::CallbackInfo& info) :
        Napi::ObjectWrap<UICommon_GameFile>(info),
        iface{} {
    iface = IUICommon_GameFile_Factory->create(asStrUtf8(info[0]).c_str());
}

UICommon_GameFile::~UICommon_GameFile() {
    IUICommon_GameFile_Factory->destroy(iface);
    free(iface);
}

Napi::Value UICommon_GameFile::_isValid(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isValid(iface));
}

Napi::Value UICommon_GameFile::_getFilePath(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getFilePath(iface)));
}

Napi::Value UICommon_GameFile::_getName(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(
            iface->getName(iface, dol_UICommon_GameFile_Variant_LongAndNotCustom)));
}

Napi::Value UICommon_GameFile::_getMaker(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(
            iface->getMaker(iface, dol_UICommon_GameFile_Variant_LongAndNotCustom)));
}

Napi::Value UICommon_GameFile::_getDescription(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(
            iface->getDescription(iface, dol_UICommon_GameFile_Variant_LongAndNotCustom)));
}

Napi::Value UICommon_GameFile::_getLanguages(const Napi::CallbackInfo& info) {
    int numLanguages;
    auto languages = iface->getLanguages(iface, &numLanguages);
    auto a = Napi::Array::New(info.Env(), numLanguages);
    for (int i{}; i < numLanguages; ++i)
        a.Set(i, fromS32(info.Env(), languages[i]));
    free(languages);
    return a;
}

Napi::Value UICommon_GameFile::_getInternalName(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getInternalName(iface)));
}

Napi::Value UICommon_GameFile::_getGameID(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getGameID(iface)));
}

Napi::Value UICommon_GameFile::_getGameTDBID(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getGameTDBID(iface)));
}

Napi::Value UICommon_GameFile::_getTitleID(const Napi::CallbackInfo& info) {
    return fromU64_n(info.Env(), iface->getTitleID(iface));
}

Napi::Value UICommon_GameFile::_getMakerID(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getMakerID(iface)));
}

Napi::Value UICommon_GameFile::_getRevision(const Napi::CallbackInfo& info) {
    return fromU16(info.Env(), iface->getRevision(iface));
}

Napi::Value UICommon_GameFile::_getDiscNumber(const Napi::CallbackInfo& info) {
    return fromU8(info.Env(), iface->getDiscNumber(iface));
}

Napi::Value UICommon_GameFile::_getSyncHash(const Napi::CallbackInfo& info) {
    uint8_t hash[20]{};
    iface->getSyncHash(iface, hash);
    return Napi::Buffer<uint8_t>::Copy(info.Env(), hash, 20);
}

Napi::Value UICommon_GameFile::_getWiiFSPath(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getWiiFSPath(iface)));
}

Napi::Value UICommon_GameFile::_getRegion(const Napi::CallbackInfo& info) {
    return fromS32(info.Env(), iface->getRegion(iface));
}

Napi::Value UICommon_GameFile::_getCountry(const Napi::CallbackInfo& info) {
    return fromS32(info.Env(), iface->getCountry(iface));
}

Napi::Value UICommon_GameFile::_getPlatform(const Napi::CallbackInfo& info) {
    return fromS32(info.Env(), iface->getPlatform(iface));
}

Napi::Value UICommon_GameFile::_getBlobType(const Napi::CallbackInfo& info) {
    return fromS32(info.Env(), iface->getBlobType(iface));
}

Napi::Value UICommon_GameFile::_getBlockSize(const Napi::CallbackInfo& info) {
    return fromU64_n(info.Env(), iface->getBlockSize(iface));
}

Napi::Value UICommon_GameFile::_getCompressionMethod(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getCompressionMethod(iface)));
}

Napi::Value UICommon_GameFile::_getFileFormatName(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getFileFormatName(iface)));
}

Napi::Value UICommon_GameFile::_getApploaderDate(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getApploaderDate(iface)));
}

Napi::Value UICommon_GameFile::_getFileSize(const Napi::CallbackInfo& info) {
    return fromU64_n(info.Env(), iface->getFileSize(iface));
}

Napi::Value UICommon_GameFile::_getVolumeSize(const Napi::CallbackInfo& info) {
    return fromU64_n(info.Env(), iface->getVolumeSize(iface));
}

Napi::Value UICommon_GameFile::_getVolumeSizeType(const Napi::CallbackInfo& info) {
    return fromS32(info.Env(), iface->getVolumeSizeType(iface));
}

Napi::Value UICommon_GameFile::_isDatelDisc(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isDatelDisc(iface));
}

Napi::Value UICommon_GameFile::_isNKit(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isNKit(iface));
}

Napi::Value UICommon_GameFile::_isModDescriptor(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), iface->isModDescriptor(iface));
}

Napi::Value UICommon_GameFile::_getBannerImage(const Napi::CallbackInfo& info) {
    dol_UICommon_GameBanner banner;
    iface->getBannerImage(iface, &banner);

    auto a = Napi::Object::New(info.Env());
    a.Set("buffer", Napi::Buffer<uint8_t>::New(info.Env(), (uint8_t*)banner.buffer, banner.size * sizeof(uint32_t)));
    a.Set("width", fromU32(info.Env(), banner.width));
    a.Set("height", fromU32(info.Env(), banner.height));
    return a;
}

Napi::Value UICommon_GameFile::_getLocalIniPath(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), util::copyString(iface->getLocalIniPath(iface)));
}
