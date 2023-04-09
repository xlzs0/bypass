#include <Windows.h>
#include "utils.h"

#define SERVER_VERSION 13764

DWORD WINAPI Main(LPVOID base) {
    const auto version = *reinterpret_cast<uint32_t**>(PatternScan(GetModuleHandleA("engine.dll"), "FF 35 ? ? ? ? 8D 4C 24 10") + 2);

    while (!(GetAsyncKeyState(VK_DELETE) & (1 << 16))) {
        *version = SERVER_VERSION;

        Sleep(1000);
    }

    FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
}

BOOL WINAPI DllMain(HINSTANCE base, DWORD reason, LPVOID reserved) {
    if (reason != DLL_PROCESS_ATTACH) {
        return TRUE;
    }
    
    DisableThreadLibraryCalls(base);
    CreateThread(nullptr, 0, Main, base, 0, nullptr);
    
    return TRUE;
}
