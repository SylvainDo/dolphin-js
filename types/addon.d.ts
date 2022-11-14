export namespace Dolphin {
    interface LibraryInfo {
        libraryPath: string;
        libraryName?: string;
    }

    interface StartupInfo {
        organizationDomain?: string;
        organizationName?: string;
        applicationName?: string;
        applicationVersion?: string;
        applicationDisplayName?: string;
        userDirectoryPath?: string;
    }

    function loadLibrary(info: LibraryInfo): void;
    function startup(info: StartupInfo): void;
    function shutdown(): void;
    function processOne(): void;
    function advanceOne(): void;
}

export namespace Enums {
    const enum AspectMode {
        Auto,
        AnalogWide,
        Analog,
        Stretch
    }

    namespace AudioCommon {
        const enum DPL2Quality {
            Lowest,
            Low,
            High,
            Highest
        }
    }

    namespace Config {
        const enum ShowCursor {
            Never,
            Constantly,
            OnMovement
        }
    }

    namespace DiscIO {
        const enum BlobType {
            PLAIN,
            DRIVE,
            DIRECTORY,
            GCZ,
            CISO,
            WBFS,
            TGC,
            WIA,
            RVZ,
            MOD_DESCRIPTOR,
            NFS
        }

        const enum Country {
            Europe,
            Japan,
            USA,
            Australia,
            France,
            Germany,
            Italy,
            Korea,
            Netherlands,
            Russia,
            Spain,
            Taiwan,
            World,
            Unknown
        }

        const enum DataSizeType {
            Accurate,
            LowerBound,
            UpperBound
        }

        const enum Language {
            Japanese,
            English,
            German,
            French,
            Spanish,
            Italian,
            Dutch,
            SimplifiedChinese,
            TraditionalChinese,
            Korean,
            Unknown
        }

        const enum Platform {
            GameCubeDisc,
            WiiDisc,
            WiiWAD,
            ELFOrDOL
        }

        const enum Region {
            NTSC_J,
            NTSC_U,
            PAL,
            Unknown,
            NTSC_K
        }
    }

    namespace ExpansionInterface {
        const enum EXIDeviceType {
            Dummy,
            MemoryCard,
            MaskROM,
            AD16,
            Microphone,
            Ethernet,
            AMBaseboard,
            Gecko,
            MemoryCardFolder,
            AGP,
            EthernetXLink,
            EthernetTapServer,
            EthernetBuiltIn,
            None = 0xff
        }

        const enum Slot {
            A,
            B,
            SP1
        }
    }

    namespace FreeLook {
        const enum ControlType {
            SixAxis,
            FPS,
            Orbital
        }
    }

    namespace HSP {
        const enum HSPDeviceType {
            None,
            ARAMExpansion
        }
    }

    namespace PowerPC {
        const enum CPUCore {
            Interpreter,
            JIT64,
            JITARM64 = 4,
            CachedInterpreter
        }
    }

    namespace SerialInterface {
        const enum SIDevices {
            None,
            N64Mic,
            N64Keyboard,
            N64Mouse,
            N64Controller,
            GC_GBA,
            GCController,
            GCKeyboard,
            GCSteering,
            DanceMat,
            GCTaruKonga,
            AMBaseboard,
            WiiUAdapter,
            GC_GBA_Emulated
        }
    }

    const enum ShaderCompilationMode {
        Synchronous,
        SynchronousUberShaders,
        AsynchronousUberShaders,
        AsynchronousSkipRendering
    }

    const enum StereoMode {
        Off,
        SBS,
        TAB,
        Anaglyph,
        QuadBuffer,
        Passive
    }

    const enum TriState {
        Off,
        On,
        Auto
    }

    const enum WiimoteSource {
        None,
        Emulated,
        Real
    }
}

export namespace Gui {
    namespace Application {
        function hasExited(): boolean;
    }

    namespace MainWindow {
        function show(): void;
        function startGame(path: string): void;
    }

    namespace Settings {
        // UI
        function setThemeName(theme_name: string): void;
        function setCurrentUserStyle(stylesheet_name: string): void;
        function getCurrentUserStyle(): string;
        function setUserStylesEnabled(enabled: boolean): void;
        function areUserStylesEnabled(): boolean;
        function isLogVisible(): boolean;
        function setLogVisible(visible: boolean): void;
        function isLogConfigVisible(): boolean;
        function setLogConfigVisible(visible: boolean): void;
        function setToolBarVisible(visible: boolean): void;
        function isToolBarVisible(): boolean;
        function setWidgetsLocked(locked: boolean): void;
        function areWidgetsLocked(): boolean;
        function refreshWidgetVisibility(): void;
        // GameList
        function getPaths(): string[];
        function addPath(path: string): void;
        function removePath(path: string): void;
        function getPreferredView(): boolean;
        function setPreferredView(list: boolean): void;
        function getDefaultGame(): string;
        function setDefaultGame(path: string): void;
        function refreshGameList(): void;
        function refreshMetadata(): void;
        function reloadTitleDB(): void;
        function isAutoRefreshEnabled(): boolean;
        function setAutoRefreshEnabled(enabled: boolean): void;
        // Emulation
        function getStateSlot(): number;
        function setStateSlot(slot: number): void;
        function isBatchModeEnabled(): boolean;
        function setBatchModeEnabled(batch: boolean): void;
        function isSDCardInserted(): boolean;
        function setSDCardInserted(inserted: boolean): void;
        function isUSBKeyboardConnected(): boolean;
        function setUSBKeyboardConnected(connected: boolean): void;
        // Graphics
        function setCursorVisibility(hideCursor: Enums.Config.ShowCursor): void;
        function getCursorVisibility(): Enums.Config.ShowCursor;
        function setLockCursor(lock_cursor: boolean): void;
        function getLockCursor(): boolean;
        function setKeepWindowOnTop(top: boolean): void;
        function isKeepWindowOnTopEnabled(): boolean;
        function getGraphicModsEnabled(): boolean;
        function setGraphicModsEnabled(enabled: boolean): void;
        // Audio
        function getVolume(): number;
        function setVolume(volume: number): void;
        function increaseVolume(volume: number): void;
        function decreaseVolume(volume: number): void;
        // Cheats
        function getCheatsEnabled(): boolean;
        function setCheatsEnabled(enabled: boolean): void;
        // Debug
        function setDebugModeEnabled(enabled: boolean): void;
        function isDebugModeEnabled(): boolean;
        function setRegistersVisible(enabled: boolean): void;
        function isRegistersVisible(): boolean;
        function setThreadsVisible(enabled: boolean): void;
        function isThreadsVisible(): boolean;
        function setWatchVisible(enabled: boolean): void;
        function isWatchVisible(): boolean;
        function setBreakpointsVisible(enabled: boolean): void;
        function isBreakpointsVisible(): boolean;
        function setCodeVisible(enabled: boolean): void;
        function isCodeVisible(): boolean;
        function setMemoryVisible(enabled: boolean): void;
        function isMemoryVisible(): boolean;
        function setNetworkVisible(enabled: boolean): void;
        function isNetworkVisible(): boolean;
        function setJITVisible(enabled: boolean): void;
        function isJITVisible(): boolean;
        // Fallback Region
        function getFallbackRegion(): Enums.DiscIO.Region;
        function setFallbackRegion(region: Enums.DiscIO.Region): void;
    }
}

export namespace AddressSpace {
    const enum Type {
        Effective,
        Auxiliary,
        Physical,
        Mem1,
        Mem2,
        Fake
    }

    function isValidAddress(address_space: Type, address: number): boolean;
    function get(address_space: Type): ArrayBuffer;
    function slice(address_space: Type, start: number, end?: number): ArrayBuffer;
    function search(address_space: Type, haystack_offset: number, needle: Uint8Array, forward?: boolean): number | undefined;
}

export namespace Config {
    function getInt(prop: string, ...args: any[]): number;
    function getBool(prop: string, ...args: any[]): boolean;
    function getString(prop: string, ...args: any[]): string;
    function getFloat(prop: string, ...args: any[]): number;
    function getUint16(prop: string, ...args: any[]): number;
    function getUint32(prop: string, ...args: any[]): number;
    function setInt(prop: string, ...args: any[]): void;
    function setBool(prop: string, ...args: any[]): void;
    function setString(prop: string, ...args: any[]): void;
    function setFloat(prop: string, ...args: any[]): void;
    function setUint16(prop: string, ...args: any[]): void;
    function setUint32(prop: string, ...args: any[]): void;
}

export namespace Core {
    function getActualEmulationSpeed(): number;
    function displayMessage(message: string, time_in_ms: number): void;
}

export namespace JitInterface {
    function clearCache(): void;
    function invalidateICache(address: number, size: number): void;
    function invalidateICacheLines(address: number, count: number): void;
}

export namespace Memory {
    function memset(address: number, value: number, size: number | bigint): void;
    function readU8(address: number): number;
    function readU16LE(address: number): number;
    function readU32LE(address: number): number;
    function readU64LE(address: number): bigint;
    function readF32LE(address: number): number;
    function readF64LE(address: number): number;
    function readU16BE(address: number): number;
    function readU32BE(address: number): number;
    function readU64BE(address: number): bigint;
    function readF32BE(address: number): number;
    function readF64BE(address: number): number;
    function readS8(address: number): number;
    function readS16LE(address: number): number;
    function readS32LE(address: number): number;
    function readS64LE(address: number): bigint;
    function readS16BE(address: number): number;
    function readS32BE(address: number): number;
    function readS64BE(address: number): bigint;
    function readBufferU8(address: number, size: number): Uint8Array;
    function readBitU8(address: number, bit_offset: number): boolean;
    function readBitsU8(address: number): Uint8Array;
    function readBitsBufferU8(address: number, size: number): Uint8Array;
    function writeU8(address: number, value: number): void;
    function writeU16LE(address: number, value: number): void;
    function writeU32LE(address: number, value: number): void;
    function writeU64LE(address: number, value: number | bigint): void;
    function writeF32LE(address: number, value: number): void;
    function writeF64LE(address: number, value: number): void;
    function writeU16BE(address: number, value: number): void;
    function writeU32BE(address: number, value: number): void;
    function writeU64BE(address: number, value: number | bigint): void;
    function writeF32BE(address: number, value: number): void;
    function writeF64BE(address: number, value: number): void;
    function writeBufferU8(address: number, data: Uint8Array): void;
    function writeBitU8(address: number, bit_offset: number, set: number | boolean): void;
    function writeBitsU8(address: number, data: Uint8Array): void;
    function writeBitsBufferU8(address: number, data: Uint8Array): void;
    function readPtrU8(address: number, offset: number): number;
    function readPtrU16LE(address: number, offset: number): number;
    function readPtrU32LE(address: number, offset: number): number;
    function readPtrU64LE(address: number, offset: number): bigint;
    function readPtrF32LE(address: number, offset: number): number;
    function readPtrF64LE(address: number, offset: number): number;
    function readPtrU16BE(address: number, offset: number): number;
    function readPtrU32BE(address: number, offset: number): number;
    function readPtrU64BE(address: number, offset: number): bigint;
    function readPtrF32BE(address: number, offset: number): number;
    function readPtrF64BE(address: number, offset: number): number;
    function readPtrS8(address: number, offset: number): number;
    function readPtrS16LE(address: number, offset: number): number;
    function readPtrS32LE(address: number, offset: number): number;
    function readPtrS64LE(address: number, offset: number): bigint;
    function readPtrS16BE(address: number, offset: number): number;
    function readPtrS32BE(address: number, offset: number): number;
    function readPtrS64BE(address: number, offset: number): bigint;
    function readPtrBufferU8(address: number, offset: number, size: number): Uint8Array;
    function readPtrBitU8(address: number, offset: number, bit_offset: number): boolean;
    function readPtrBitsU8(address: number, offset: number): Uint8Array;
    function readPtrBitsBufferU8(address: number, offset: number, size: number): Uint8Array;
    function writePtrU8(address: number, offset: number, value: number): void;
    function writePtrU16LE(address: number, offset: number, value: number): void;
    function writePtrU32LE(address: number, offset: number, value: number): void;
    function writePtrU64LE(address: number, offset: number, value: number | bigint): void;
    function writePtrF32LE(address: number, offset: number, value: number): void;
    function writePtrF64LE(address: number, offset: number, value: number): void;
    function writePtrU16BE(address: number, offset: number, value: number): void;
    function writePtrU32BE(address: number, offset: number, value: number): void;
    function writePtrU64BE(address: number, offset: number, value: number | bigint): void;
    function writePtrF32BE(address: number, offset: number, value: number): void;
    function writePtrF64BE(address: number, offset: number, value: number): void;
    function writePtrBufferU8(address: number, offset: number, data: Uint8Array): void;
    function writePtrBitU8(address: number, offset: number, bit_offset: number, set: number | boolean): void;
    function writePtrBitsU8(address: number, offset: number, data: Uint8Array): void;
    function writePtrBitsBufferU8(address: number, offset: number, data: Uint8Array): void;
}

export namespace Pad {
    namespace GC {
        const enum Buttons {
            Left = 0x0001,
            Right = 0x0002,
            Down = 0x0004,
            Up = 0x0008,
            Trigger_Z = 0x0010,
            Trigger_R = 0x0020,
            Trigger_L = 0x0040,
            A = 0x0100,
            B = 0x0200,
            X = 0x0400,
            Y = 0x0800,
            Start = 0x1000
        }

        interface Status {
            readonly button: Buttons;
            readonly stickX: number;
            readonly stickY: number;
            readonly substickX: number;
            readonly substickY: number;
            readonly triggerLeft: number;
            readonly triggerRight: number;
            readonly analogA: number;
            readonly analogB: number;
            readonly isConnected: number;
        }

        function getStatus(pad_num: number): Status;
        function rumble(pad_num: number, strength: number): void;
        function resetRumble(pad_num: number): void;
    }
}

export namespace UICommon {
    function formatSize(bytes: number | bigint, decimals: number): string;
}
