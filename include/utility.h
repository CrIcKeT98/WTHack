#pragma once
#include <Windows.h>
#include <d3d11.h>

#include "menu.h"
#include "gamedata/gamedata.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

struct WTHack_vars {
	Present oPresent = NULL;
	HWND hWindow = NULL;
	WNDPROC oWndProc = NULL;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* pTargetView;

	GameData* game = NULL;
	Menu* menu = NULL;
};