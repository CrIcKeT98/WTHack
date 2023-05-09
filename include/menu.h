#pragma once

#include <d3d11.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"

class Menu {
public:
	static Menu* instance();
	void init(IDXGISwapChain* pSwapChain);
	bool isInitialized();
	void drawMenu();

	bool draw;

private:
	Menu() = default;
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;

	//Check boxes
	bool is_init = false;
	bool lead_marker;
	bool bombsight;
	bool ccrp;
};