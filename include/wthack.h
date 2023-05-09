#pragma once
#include <Windows.h>

#include "hooks.h"
#include "utility.h"
#include "menu.h"

#define IMGUI_DEFINE_MATH_OPERATORS
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
