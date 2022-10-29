export interface StartupInfo {
    organizationDomain?: string;
    organizationName?: string;
    applicationName?: string;
    applicationVersion?: string;
    applicationDisplayName?: string;
    libraryPath: string;
    libraryName?: string;
}

export function startup(si: StartupInfo): void;

export const enum AspectMode {
    Auto,
    AnalogWide,
    Analog,
    Stretch
}

export namespace AudioCommon {
    const enum DPL2Quality {
        Lowest = 0,
        Low = 1,
        High = 2,
        Highest = 3
    }
}

export namespace Config {
    const enum GPUDeterminismMode {
        Auto,
        Disabled,
        FakeCompletion
    }

    const enum LayerType {
        Base,
        CommandLine,
        GlobalGame,
        LocalGame,
        Movie,
        Netplay,
        CurrentRun,
        Meta
    }

    const enum ShowCursor {
        Never,
        Constantly,
        OnMovement
    }

    const enum System {
        Main,
        SYSCONF,
        GCPad,
        WiiPad,
        GCKeyboard,
        GFX,
        Logger,
        Debugger,
        DualShockUDPClient,
        FreeLook,
        Session
    }
}

export namespace DiscIO {
    const enum Language {
        Japanese = 0,
        English = 1,
        German = 2,
        French = 3,
        Spanish = 4,
        Italian = 5,
        Dutch = 6,
        SimplifiedChinese = 7,
        TraditionalChinese = 8,
        Korean = 9,
        Unknown
    }

    const enum Region {
        NTSC_J = 0,
        NTSC_U = 1,
        PAL = 2,
        Unknown = 3,
        NTSC_K = 4
    }
}

export namespace ExpansionInterface {
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
        None = 0xFF
    }

    const enum Slot {
        A,
        B,
        SP1
    }
}

export namespace FreeLook {
    const enum ControlType {
        SixAxis,
        FPS,
        Orbital
    }
}

export namespace HSP {
    const enum HSPDeviceType {
        None,
        ARAMExpansion
    }
}

export namespace PowerPC {
    const enum CPUCore {
        Interpreter = 0,
        JIT64 = 1,
        JITARM64 = 4,
        CachedInterpreter = 5
    }
}

export namespace SerialInterface {
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
        GC_GBA_Emulated,
        Count
    }
}

export const enum ShaderCompilationMode {
    Synchronous,
    SynchronousUberShaders,
    AsynchronousUberShaders,
    AsynchronousSkipRendering
}

export const enum StereoMode {
    Off,
    SBS,
    TAB,
    Anaglyph,
    QuadBuffer,
    Passive
}

export const enum TriState {
    Off,
    On,
    Auto
}

export const enum WiimoteSource {
    None = 0,
    Emulated = 1,
    Real = 2
}

export namespace Gui {
    namespace Application {
        function init(): void;
        function shutdown(): void;
        function hasExited(): boolean;
        function processEvents(): void;
    }

    namespace Host {
        function deleteLater(): void;
        function declareAsHostThread(): void;
        function isHostThread(): boolean;
    }

    namespace MainWindow {
        function init(): void;
        function shutdown(): void;
        function show(): void;
        function requestStop(): boolean;
        function startGame(path: string): void;
    }

    namespace Resources {
        function init(): void;
    }

    namespace Settings {
        function unregisterDevicesChangedCallback(): void;
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
        function notifyRefreshGameListStarted(): void;
        function notifyRefreshGameListComplete(): void;
        function refreshMetadata(): void;
        function notifyMetadataRefreshComplete(): void;
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
        function setCursorVisibility(hideCursor: Config.ShowCursor): void;
        function getCursorVisibility(): Config.ShowCursor;
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
        // Auto-Update
        function getAutoUpdateTrack(): string;
        function setAutoUpdateTrack(mode: string): void;
        // Fallback Region
        function getFallbackRegion(): DiscIO.Region;
        function setFallbackRegion(region: DiscIO.Region): void;
        // Analytics
        function isAnalyticsEnabled(): boolean;
        function setAnalyticsEnabled(enabled: boolean): void;
    }

    namespace Translation {
        function initialize(): void;
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
    function getDefaultLanguage(): DiscIO.Language;
    function getOptionalDefaultCountry(): DiscIO.Region | undefined;
    function getDefaultCountry(): number;
    function getDefaultRegion(): DiscIO.Region;
    function getGPUDeterminismMode(): GPUDeterminismMode;
    function shouldUseDPL2Decoder(): boolean;
    function getIsoPaths(): string[];
    function setIsoPaths(paths: string[]): void;
    function getUSBDeviceWhitelist(): number[][];
    function setUSBDeviceWhitelist(devices: number[][]): void;
    function toGameCubeRegion(region: DiscIO.Region): DiscIO.Region;
    function getDirectoryForRegion(region: DiscIO.Region): string;
    function getBootROMPath(region_directory: string): string;
    function getMemcardPath(slot: ExpansionInterface.Slot, region: DiscIO.Region | undefined, size_mb: number): string;
    function getMemcardPath(configured_filename: string, slot: ExpansionInterface.Slot, region: DiscIO.Region | undefined, size_mb: number): string;
    function isDefaultMemcardPathConfigured(slot: ExpansionInterface.Slot): boolean;
}

export namespace Core {
    function getActualEmulationSpeed(): number;
    function shutdown(): void;
    function displayMessage(message: string, time_in_ms: number): void;
    function hostDispatchJobs(): void;
}

export namespace DolphinAnalytics {
    function reloadConfig(): void;
    function generateNewIdentity(): void;
}

export namespace UICommon {
    function init(): void;
    function shutdown(): void;
    function setLocale(locale_name: string): void;
    function createDirectories(): void;
    function setUserDirectory(custom_path: string): void;
    function triggerSTMPowerEvent(): boolean;
    function formatSize(bytes: number | bigint, decimals: number): string;
}
