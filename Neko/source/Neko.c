#include "Neko.h"

WNDCLASSEXW CreateWindowClassW(LPWSTR Name, LRESULT ClassProc, COLORREF BackgroundColor, LPCWSTR Cursor, LPWSTR Icon) {
	WNDCLASSEXW wcl;
	memset(&wcl, 0, sizeof(wcl));

	wcl.cbSize = sizeof(WNDCLASSEX);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.cbClsExtra = 0;
	wcl.lpszClassName = Name;
	wcl.lpfnWndProc = ClassProc;
	wcl.hbrBackground = CreateSolidBrush(BackgroundColor);
	wcl.hCursor = LoadCursorW(0, Cursor);
	wcl.cbWndExtra = 0;
	wcl.hIcon = LoadIconW(GetModuleHandle(0), MAKEINTRESOURCEW(Icon));

	RegisterClassExW(&wcl);

	return wcl;
}

void ShowAllWindow(int Style, HWND Windows, ...) {
	HWND(*Window) = &Windows;
	while (*Window) {
		ShowWindow(*Window, Style);
		Window++;
	}
}