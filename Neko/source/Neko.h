#include <Windows.h>
#include "resource.h"

#define UP 0x1000
#define DOWN 0x100
#define RIGHT 0x1
#define LEFT 0x10

#define NekoStay IDI_ICON1
#define NekoUP1 IDI_ICON2
#define NekoUP2 IDI_ICON3
#define NekoUPandRIGHT1 IDI_ICON4
#define NekoUPandRIGHT2 IDI_ICON5
#define NekoRIGHT1 IDI_ICON6
#define NekoRIGHT2 IDI_ICON7
#define NekoDOWNandRIGHT1 IDI_ICON8
#define NekoDOWNandRIGHT2 IDI_ICON9
#define NekoDOWN1 IDI_ICON10
#define NekoDOWN2 IDI_ICON11
#define NekoDOWNandLEFT1 IDI_ICON12
#define NekoDOWNandLEFT2 IDI_ICON13
#define NekoLEFT1 IDI_ICON14
#define NekoLEFT2 IDI_ICON15
#define NekoLEFTandUP1 IDI_ICON16
#define NekoLEFTandUP2 IDI_ICON17
#define NekoSCRATCH1 IDI_ICON18
#define NekoSCRATCH2 IDI_ICON19
#define NekoYAWNS IDI_ICON20
#define NekoSLEEP1 IDI_ICON21
#define NekoSLEEP2 IDI_ICON22
#define NekoAwake IDI_ICON23
#define NekoBreath IDI_ICON24
#define NekoALMOSTSLEEP IDI_ICON25
#define NekoAwakeFromSLEEP IDI_ICON26

#define WM_USER_SHELLICON (WM_USER + 1)

#define NekoSpeed 1

WNDCLASSEXW CreateWindowClassW(LPWSTR Name, LRESULT ClassProc, COLORREF BackgroundColor, LPCWSTR Cursor, LPWSTR Icon);
void ShowAllWindow(int Style, HWND Windows, ...);