#include <iostream>

#include "wthack.h"
#include "memory.h"
#include "gamedata/gamedata.h"
#include <vector>
#include <iomanip>
#include "gamedata/units.h"
#include <TlHelp32.h>

WTHack_vars gVars;
DWORD ProcessId = 0;

DWORD GetProcId(const char* ProcName)
{
	PROCESSENTRY32   pe32;
	HANDLE         hSnapshot = NULL;

	pe32.dwSize = sizeof(PROCESSENTRY32);
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(hSnapshot, &pe32))
	{
		do {
			if (strcmp(pe32.szExeFile, ProcName) == 0)
				break;
		} while (Process32Next(hSnapshot, &pe32));
	}

	if (hSnapshot != INVALID_HANDLE_VALUE)
		CloseHandle(hSnapshot);

	return pe32.th32ProcessID;
}

DWORD WINAPI WTHackThread(LPVOID instance)
{
	gVars.menu = Menu::instance();
	gVars.game = GameData::instance();

	if (kiero::init(kiero::RenderType::Auto) == kiero::Status::Success)
	{
		kiero::bind(8, (void**)&gVars.oPresent, hkPresent);
	}

	gVars.game->init();

#ifndef NDEBUG
	AllocConsole();

	FILE* fp;
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
#endif

	while (1) {
		if (GetAsyncKeyState(VK_END)) {
			break;
		}
		if (GetAsyncKeyState(VK_HOME) & 0x01) {
			gVars.game->update();
			gVars.game->print();

		}
		if (GetAsyncKeyState(VK_INSERT) & 0x01) {
			gVars.menu->draw = !gVars.menu->draw;
			gVars.game->hud->air_leading_indicator = true;
		}
		if (GetAsyncKeyState(VK_DELETE) & 0x01) {
			std::uintptr_t t = memory::scan("0F 29 74 24 30 C6 44 24 20 00 48 8D 7C 24 30 4C 8D 44 24 20 48 89 F1 48 89 FA");
			if (t == 0)
				continue;

			std::cout << std::hex << air_leading_hook << std::endl;
			std::vector<std::uint8_t> data{};
			
			ProcessId = GetProcId("aces.exe");
			if (!ProcessId){
				std::cout << "ProcessId = 0!" << std::endl;
				continue;
			}

			HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);

			if (hProc == INVALID_HANDLE_VALUE || !hProc)
			{
				std::cout << "Failed to open process" << std::endl;
				continue;
			}

			DWORD OldProtect_Function = 0;
			if (!VirtualProtectEx(hProc, (LPVOID)t, sizeof(DWORD)*4, PAGE_EXECUTE_READWRITE, &OldProtect_Function))
			{
				std::cout << "VirtualProtectEx (1) failed with status: " << GetLastError() << std::endl;
				CloseHandle(hProc);
				continue;
			}
			
			//mov to rax air_leading_hook
			//mov to rcx return addr
			//jmp [rax]
			//48 b8 8-byte address ff e0
			//return to 7FF7625141CD
			for (size_t i = 0; i < 26; ++i) {
				data.push_back(*(std::uint8_t*)(t + i));
			}

			std::vector<std::uint8_t> hack{ 0x48, 0xb8 };
			for (uintptr_t x = (uintptr_t)air_leading_hook, i = 0; i < 8; ++i) {
				hack.push_back(x & 0xFF);
				x >>= 8;
			}

			hack.push_back(0x48);
			hack.push_back(0xBA);
			for (uintptr_t x = t + 23, i = 0; i < 8; ++i) {
				hack.push_back(x & 0xFF);
				x >>= 8;
			}

			hack.push_back(0xFF);
			hack.push_back(0xE0);
			hack.push_back(0x90);

			for (size_t i = 0; i < hack.size(); ++i) {
				*((std::uint8_t*)t + i) = hack[i];
			}

			VirtualProtectEx(hProc, (LPVOID)t, sizeof(DWORD) * 4, OldProtect_Function, &OldProtect_Function);
			CloseHandle(hProc);
		}

		Sleep(200);
	}

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);

		if (const HANDLE h = CreateThread(nullptr, 0, WTHackThread, hModule, 0, nullptr))
			CloseHandle(h);

		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		SetWindowLongPtrW(gVars.hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(gVars.oWndProc));

#ifndef NDEBUG
		HWND h_console = GetConsoleWindow();
		FreeConsole();
		PostMessage(h_console, WM_CLOSE, 0, 0);
#endif

		break;
	}

	return TRUE;
}

