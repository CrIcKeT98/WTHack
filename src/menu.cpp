#include "menu.h"
#include "utility.h"

extern WTHack_vars gVars;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(gVars.oWndProc, hWnd, uMsg, wParam, lParam);
}

Menu* Menu::instance() {
	static Menu inst;
	return &inst;
}

void Menu::init(IDXGISwapChain* pSwapChain) {
	if (!is_init) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&gVars.pDevice))) {
			gVars.pDevice->GetImmediateContext(&gVars.pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			ID3D11Texture2D* pBackBuffer = nullptr;

			pSwapChain->GetDesc(&sd);
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			gVars.hWindow = sd.OutputWindow;
			gVars.pDevice->CreateRenderTargetView(pBackBuffer, NULL, &gVars.pTargetView);
			gVars.oWndProc = (WNDPROC)SetWindowLongPtr(gVars.hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
			
			pBackBuffer->Release();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			ImGui_ImplWin32_Init(gVars.hWindow);
			ImGui_ImplDX11_Init(gVars.pDevice, gVars.pContext);

			is_init = true;
		}
	}
}

void Menu::drawMenu() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("WTHack menu");

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Aircraft"))
		{
			ImGui::Checkbox("Lead marker", &lead_marker);
			ImGui::Checkbox("Bombsight", &bombsight);
			ImGui::Checkbox("CCRP", &ccrp);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Tanks"))
		{
			ImGui::Checkbox("Светофор", &lead_marker);
			ImGui::Checkbox("Маркера", &bombsight);
			ImGui::Checkbox("Рофлан ебало", &ccrp);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();


	ImGui::Render();

	gVars.pContext->OMSetRenderTargets(1, &gVars.pTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

bool Menu::isInitialized() {
	return is_init;
}
