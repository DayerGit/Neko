#include "Neko.h"

HICON NekoIC;

LRESULT WINAPI NekoWindowProcW(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_PAINT: {
		PAINTSTRUCT PS;
		HDC WindowDC = BeginPaint(hwnd, &PS);
		HBRUSH Brush = CreateSolidBrush(RGB(0, 255, 255));
		FillRect(WindowDC, &PS.rcPaint, Brush);
		DrawIconEx(WindowDC, 0, 0, NekoIC, 0, 0, 0, 0, DI_CHANNEL | DI_IMAGE);
		EndPaint(hwnd, &PS);
		DeleteObject(Brush);
		DeleteDC(WindowDC);
		break;
	}
	case WM_USER_SHELLICON: {
		switch (lparam) {
		case WM_RBUTTONDOWN: {
			SetForegroundWindow(hwnd);
			POINT MousePos; GetCursorPos(&MousePos);
			HMENU ExitMenu = CreatePopupMenu();
			AppendMenuW(ExitMenu, MF_STRING, 0, L"Выход");
			TrackPopupMenu(ExitMenu, TPM_RIGHTBUTTON, MousePos.x, MousePos.y, 0, hwnd, NULL);
			break;
		}
		}
		break;
	}
	case WM_COMMAND: 
	case WM_DESTROY: PostQuitMessage(0);
	default: return DefWindowProcW(hwnd, msg, wparam, lparam);
	}
	return 0;
}

void MoveNeko(HWND NekoWindow) {
	POINT CurPos;
	RECT NekoPos;
	unsigned int Direction = 0;
	int OneorTwo = 0, count = 0;

	while (1) {
		Direction = 0; 
		if (count == 20) {
			OneorTwo = !OneorTwo;
			count = 0;
		}
		else count++;

		GetCursorPos(&CurPos); GetWindowRect(NekoWindow, &NekoPos);
		if (CurPos.y > NekoPos.top) {
			SetWindowPos(NekoWindow, 0, NekoPos.left, NekoPos.top + NekoSpeed, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			GetWindowRect(NekoWindow, &NekoPos);
			Direction = DOWN;
		}
		if (CurPos.y < NekoPos.top) {
			SetWindowPos(NekoWindow, 0, NekoPos.left, NekoPos.top - NekoSpeed, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			GetWindowRect(NekoWindow, &NekoPos);
			Direction = UP;
		}
		if (CurPos.x > NekoPos.left) {
			SetWindowPos(NekoWindow, 0, NekoPos.left + NekoSpeed, NekoPos.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			GetWindowRect(NekoWindow, &NekoPos);
			Direction = (Direction | RIGHT);
		}
		if (CurPos.x < NekoPos.left) {
			SetWindowPos(NekoWindow, 0, NekoPos.left - NekoSpeed, NekoPos.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			Direction = (Direction | LEFT);
		}

		if(Direction == DOWN) NekoIC = LoadIconW(GetModuleHandle(0), (OneorTwo == 1 ? NekoDOWN1 : NekoDOWN2));
		else if (Direction == UP) NekoIC = LoadIconW(GetModuleHandle(0), (OneorTwo == 1 ? NekoUP1 : NekoUP2));
		else if (Direction == RIGHT) NekoIC = LoadIconW(GetModuleHandle(0), (OneorTwo == 1 ? NekoRIGHT1 : NekoRIGHT2));
		else if (Direction == LEFT) NekoIC = LoadIconW(GetModuleHandle(0), (OneorTwo == 1 ? NekoLEFT1 : NekoLEFT2));

		else if (Direction == (DOWN | RIGHT)) NekoIC = LoadIconW(GetModuleHandle(0), (OneorTwo == 1 ? NekoDOWNandRIGHT1 : NekoDOWNandRIGHT2));
		else if (Direction == (DOWN | LEFT)) NekoIC = LoadIconW(GetModuleHandle(0), (OneorTwo == 1 ? NekoDOWNandLEFT1 : NekoDOWNandLEFT2));
		else if (Direction == (UP | RIGHT)) NekoIC = LoadIconW(GetModuleHandle(0), (OneorTwo == 1 ? NekoUPandRIGHT1 : NekoUPandRIGHT2));
		else if (Direction == (UP | LEFT)) NekoIC = LoadIconW(GetModuleHandle(0), (OneorTwo == 1 ? NekoLEFTandUP1 : NekoLEFTandUP2));

		else NekoIC = LoadIconW(GetModuleHandle(0), NekoStay);
		InvalidateRect(NekoWindow, 0, 0);
		Sleep(10);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	NekoIC = LoadIconW(GetModuleHandle(0), NekoStay);
	CreateWindowClassW(L"Neko", NekoWindowProcW, RGB(0, 255, 255), IDC_ARROW, NekoStay);

	HWND Neko = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE, L"Neko", L"Neko", WS_POPUP, 30, 30, 50, 50, 0, 0, 0, 0);

	COLORREF color = RGB(0, 255, 255);
	SetLayeredWindowAttributes(Neko, color, (BYTE)0, LWA_COLORKEY);

	ShowAllWindow(SW_SHOW, Neko, 0);

	NOTIFYICONDATA data; memset(&data, 0, sizeof(data));
	data.cbSize = sizeof(data);
	data.hWnd = Neko;
	data.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	data.uCallbackMessage = WM_USER_SHELLICON;
	data.hIcon = LoadIconW(GetModuleHandle(0), MAKEINTRESOURCEW(NekoStay));
	lstrcpynW(data.szTip, L"Neko\0", 6);

	Shell_NotifyIconW(NIM_ADD, &data);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE) MoveNeko, Neko, 0, 0);

	MSG message;
	while (GetMessage(&message, 0, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}

	return 0;
}