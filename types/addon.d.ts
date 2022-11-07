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

export namespace UICommon {
    function formatSize(bytes: number | bigint, decimals: number): string;
}
