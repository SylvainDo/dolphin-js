#include "../dol.hpp"
#include "../util.hpp"
#include "../valueConverter.hpp"
using namespace valueConverter;

#include <bit>
#include <bitset>
#include <vector>

#define bswap16 _byteswap_ushort
#define bswap32 _byteswap_ulong
#define bswap64 _byteswap_uint64

static Napi::Value readBufferU8(Napi::Env env, uint32_t address, uint32_t size) {
    std::vector<uint8_t> buf(size);
    for (uint32_t i{}; i < size; ++i)
        buf[i] = IMemory->readU8(address + i);
    return Napi::Buffer<uint8_t>::Copy(env, buf.data(), buf.size());
}

static Napi::Value readBitU8(Napi::Env env, uint32_t address, uint32_t bit_offset) {
    return fromBool(env, std::bitset<8>(IMemory->readU8(address)).test(7 - bit_offset));
}

static Napi::Value readBitsU8(Napi::Env env, uint32_t address) {
    auto data = Napi::Uint8Array::New(env, 8);
    std::bitset<8> bitset(IMemory->readU8(address));
    for (uint32_t j{}; j < 8; ++j)
        data.Set(j, fromU8(env, bitset.test(7 - j)));
    return data;
}

static Napi::Value readBitsBufferU8(Napi::Env env, uint32_t address, uint32_t size) {
    auto data = Napi::Uint8Array::New(env, size * 8);
    for (uint32_t i{}; i < size; ++i) {
        std::bitset<8> bitset(IMemory->readU8(address + i));
        for (uint32_t j{}; j < 8; ++j)
            data.Set(i * 8 + j, fromU8(env, bitset.test(7 - j)));
    }
    return data;
}

static void writeBufferU8(uint32_t address, Napi::Uint8Array data) {
    for (uint32_t i{}; i < data.ElementLength(); ++i)
        IMemory->writeU8(address + i, asU8(data.Get(i)));
}

static void writeBitU8(uint32_t address, uint32_t bit_offset, bool set) {
    std::bitset<8> bitset(IMemory->readU8(address));
    bitset.set(7 - bit_offset, set);
    IMemory->writeU8(address, static_cast<uint8_t>(bitset.to_ulong()));
}

static void writeBitsU8(uint32_t address, Napi::Uint8Array data) {
    std::bitset<8> bitset;
    for (uint32_t j{}; j < 8; ++j)
        bitset.set(7 - j, toBool(data.Get(j)));
    IMemory->writeU8(address, static_cast<uint8_t>(bitset.to_ulong()));
}

static void writeBitsBufferU8(uint32_t address, Napi::Uint8Array data) {
    for (uint32_t i{}; i < data.ElementLength() / 8; ++i) {
        std::bitset<8> bitset;
        for (uint32_t j{}; j < 8; ++j)
            bitset.set(7 - j, toBool(data.Get(i * 8 + j)));
        IMemory->writeU8(address + i, static_cast<uint8_t>(bitset.to_ulong()));
    }
}

inline uint32_t readPtrAddOffset(const Napi::CallbackInfo& info) {
    return IMemory->readU32(asU32(info[0])) + asU32(info[1]);
}

Napi::Object Memory_exports(Napi::Env env, Napi::Object exports) {
    exports.Set("memset", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->memset(asU32(info[0]), asU8(info[1]), asSize(info[2]));
        return info.Env().Undefined();
    }));
    exports.Set("readU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU8(info.Env(), IMemory->readU8(asU32(info[0])));
    }));
    exports.Set("readU16LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU16(info.Env(), bswap16(IMemory->readU16(asU32(info[0]))));
    }));
    exports.Set("readU32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU32(info.Env(), bswap32(IMemory->readU32(asU32(info[0]))));
    }));
    exports.Set("readU64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU64_n(info.Env(), bswap64(IMemory->readU64(asU32(info[0]))));
    }));
    exports.Set("readF32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF32(info.Env(), std::bit_cast<float>(bswap32(IMemory->readU32(asU32(info[0])))));
    }));
    exports.Set("readF64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF64(info.Env(), std::bit_cast<double>(bswap64(IMemory->readU64(asU32(info[0])))));
    }));
    exports.Set("readU16BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU16(info.Env(), IMemory->readU16(asU32(info[0])));
    }));
    exports.Set("readU32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU32(info.Env(), IMemory->readU32(asU32(info[0])));
    }));
    exports.Set("readU64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU64_n(info.Env(), IMemory->readU64(asU32(info[0])));
    }));
    exports.Set("readF32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF32(info.Env(), std::bit_cast<float>(IMemory->readU32(asU32(info[0]))));
    }));
    exports.Set("readF64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF64(info.Env(), std::bit_cast<double>(IMemory->readU64(asU32(info[0]))));
    }));
    exports.Set("readS8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS8(info.Env(), static_cast<int8_t>(IMemory->readU8(asU32(info[0]))));
    }));
    exports.Set("readS16LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS16(info.Env(), static_cast<int16_t>(bswap16(IMemory->readU16(asU32(info[0])))));
    }));
    exports.Set("readS32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), static_cast<int32_t>(bswap32(IMemory->readU32(asU32(info[0])))));
    }));
    exports.Set("readS64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS64_n(info.Env(), static_cast<int64_t>(bswap64(IMemory->readU64(asU32(info[0])))));
    }));
    exports.Set("readS16BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS16(info.Env(), static_cast<int16_t>(IMemory->readU16(asU32(info[0]))));
    }));
    exports.Set("readS32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), static_cast<int32_t>(IMemory->readU32(asU32(info[0]))));
    }));
    exports.Set("readS64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS64_n(info.Env(), static_cast<int64_t>(IMemory->readU64(asU32(info[0]))));
    }));
    exports.Set("readBufferU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return readBufferU8(info.Env(), asU32(info[0]), asU32(info[1]));
    }));
    exports.Set("readBitU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return readBitU8(info.Env(), asU32(info[0]), asU32(info[1]));
    }));
    exports.Set("readBitsU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return readBitsU8(info.Env(), asU32(info[0]));
    }));
    exports.Set("readBitsBufferU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return readBitsBufferU8(info.Env(), asU32(info[0]), asU32(info[1]));
    }));
    exports.Set("writeU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU8(asU8(info[1]), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeU16LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU16(bswap16(asU16(info[1])), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeU32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU32(bswap32(asU32(info[1])), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeU64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU64(bswap64(asU64(info[1])), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeF32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU32(bswap32(std::bit_cast<uint32_t>(asF32(info[1]))), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeF64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU64(bswap64(std::bit_cast<uint64_t>(asF64(info[1]))), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeU16BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU16(asU16(info[1]), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeU32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU32(asU32(info[1]), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeU64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU64(asU64(info[1]), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeF32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU32(std::bit_cast<uint32_t>(asF32(info[1])), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeF64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU64(std::bit_cast<uint64_t>(asF64(info[1])), asU32(info[0]));
        return info.Env().Undefined();
    }));
    exports.Set("writeBufferU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return writeBufferU8(asU32(info[0]), info[1].As<Napi::Uint8Array>());
    }));
    exports.Set("writeBitU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return writeBitU8(asU32(info[0]), asU32(info[1]), toBool(info[2]));
    }));
    exports.Set("writeBitsU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return writeBitsU8(asU32(info[0]), info[1].As<Napi::Uint8Array>());
    }));
    exports.Set("writeBitsBufferU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return writeBitsBufferU8(asU32(info[0]), info[1].As<Napi::Uint8Array>());
    }));
    exports.Set("readPtrU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU8(info.Env(), IMemory->readU8(readPtrAddOffset(info)));
    }));
    exports.Set("readPtrU16LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU16(info.Env(), bswap16(IMemory->readU16(readPtrAddOffset(info))));
    }));
    exports.Set("readPtrU32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU32(info.Env(), bswap32(IMemory->readU32(readPtrAddOffset(info))));
    }));
    exports.Set("readPtrU64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU64_n(info.Env(), bswap64(IMemory->readU64(readPtrAddOffset(info))));
    }));
    exports.Set("readPtrF32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF32(info.Env(), std::bit_cast<float>(bswap32(IMemory->readU32(readPtrAddOffset(info)))));
    }));
    exports.Set("readPtrF64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF64(info.Env(), std::bit_cast<double>(bswap64(IMemory->readU64(readPtrAddOffset(info)))));
    }));
    exports.Set("readPtrU16BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU16(info.Env(), IMemory->readU16(readPtrAddOffset(info)));
    }));
    exports.Set("readPtrU32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU32(info.Env(), IMemory->readU32(readPtrAddOffset(info)));
    }));
    exports.Set("readPtrU64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromU64_n(info.Env(), IMemory->readU64(readPtrAddOffset(info)));
    }));
    exports.Set("readPtrF32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF32(info.Env(), std::bit_cast<float>(IMemory->readU32(readPtrAddOffset(info))));
    }));
    exports.Set("readPtrF64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromF64(info.Env(), std::bit_cast<double>(IMemory->readU64(readPtrAddOffset(info))));
    }));
    exports.Set("readPtrS8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS8(info.Env(), static_cast<int8_t>(IMemory->readU8(readPtrAddOffset(info))));
    }));
    exports.Set("readPtrS16LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS16(info.Env(), static_cast<int16_t>(bswap16(IMemory->readU16(readPtrAddOffset(info)))));
    }));
    exports.Set("readPtrS32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), static_cast<int32_t>(bswap32(IMemory->readU32(readPtrAddOffset(info)))));
    }));
    exports.Set("readPtrS64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS64_n(info.Env(), static_cast<int64_t>(bswap64(IMemory->readU64(readPtrAddOffset(info)))));
    }));
    exports.Set("readPtrS16BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS16(info.Env(), static_cast<int16_t>(IMemory->readU16(readPtrAddOffset(info))));
    }));
    exports.Set("readPtrS32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS32(info.Env(), static_cast<int32_t>(IMemory->readU32(readPtrAddOffset(info))));
    }));
    exports.Set("readPtrS64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromS64_n(info.Env(), static_cast<int64_t>(IMemory->readU64(readPtrAddOffset(info))));
    }));
    exports.Set("readPtrBufferU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return readBufferU8(info.Env(), readPtrAddOffset(info), asU32(info[2]));
    }));
    exports.Set("readPtrBitU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return readBitU8(info.Env(), readPtrAddOffset(info), asU32(info[2]));
    }));
    exports.Set("readPtrBitsU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return readBitsU8(info.Env(), readPtrAddOffset(info));
    }));
    exports.Set("readPtrBitsBufferU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return readBitsBufferU8(info.Env(), readPtrAddOffset(info), asU32(info[2]));
    }));
    exports.Set("writePtrU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU8(asU8(info[2]), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrU16LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU16(bswap16(asU16(info[2])), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrU32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU32(bswap32(asU32(info[2])), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrU64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU64(bswap64(asU64(info[2])), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrF32LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU32(bswap32(std::bit_cast<uint32_t>(asF32(info[2]))), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrF64LE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU64(bswap64(std::bit_cast<uint64_t>(asF64(info[2]))), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrU16BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU16(asU16(info[2]), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrU32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU32(asU32(info[2]), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrU64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU64(asU64(info[2]), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrF32BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU32(std::bit_cast<uint32_t>(asF32(info[2])), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrF64BE", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        IMemory->writeU64(std::bit_cast<uint64_t>(asF64(info[2])), readPtrAddOffset(info));
        return info.Env().Undefined();
    }));
    exports.Set("writePtrBufferU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return writeBufferU8(readPtrAddOffset(info), info[2].As<Napi::Uint8Array>());
    }));
    exports.Set("writePtrBitU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return writeBitU8(readPtrAddOffset(info), asU32(info[2]), toBool(info[3]));
    }));
    exports.Set("writePtrBitsU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return writeBitsU8(readPtrAddOffset(info), info[2].As<Napi::Uint8Array>());
    }));
    exports.Set("writePtrBitsBufferU8", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return writeBitsBufferU8(readPtrAddOffset(info), info[2].As<Napi::Uint8Array>());
    }));
    exports.Set("readCStr", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(
                IMemory->getString(asU32(info[0]), asSizeOr(info[1], 0))));
    }));
    exports.Set("readPtrCStr", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return fromStrUtf8(info.Env(), util::copyString(
                IMemory->getString(readPtrAddOffset(info), asSizeOr(info[2], 0))));
    }));
    return exports;
}
