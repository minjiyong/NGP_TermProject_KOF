#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>
#include <atlImage.h>
#include <iostream>
#include <thread>
#include "IMAGE.h"
#include "Chin.h"
#include "Kaphwan.h"
#include "Effect.h"
#include "UI.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "winmm.lib")

using namespace std;


#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define HP 0
#define MAP1_1 1
#define MAP1_2 2
#define MAP1_3 3
#define CHINNAME 4
#define KAPNAME 5
#define KAPPROFILE 6
#define CHINPROFILE 7

#define TIME0 8
#define TIME1 9
#define TIME2 10
#define TIME3 11
#define TIME4 12
#define TIME5 13
#define TIME6 14
#define TIME7 15
#define TIME8 16
#define TIME9 17
#define START1 18
#define START2 19
#define FIGHT 20
#define KO 21

#define STANDING 0
#define NOATTACK 1

#define JUMP 2
#define FRONTMOVE 3
#define SITTING 4
#define BACKMOVE 5

#define STANDINGGUARD 6
#define SITTINGGUARD 7

#define WEAKPUNCH 8
#define STRONGPUNCH 9
#define WEAKKICK 10
#define STRONGKICK 11

#define STANDINGHIT 12
#define SITTINGHIT 13
#define JUMPHIT 14

#define NOHIT 100
#define HITTED 101
#define GUARD 102


UI ui{};

Chin Gen{};
Kaphwan Kap{};

Effect effect{};


void draw_framerectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void playbackgroundmusic();


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"KOF";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow){
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rt{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	HBITMAP hBitmap;
	HDC hDC, mDC;

	static bool mode_hitbox{ false };

	static RECT hitvoid{};
	static int hitindex{};

	static int bg = 0;
	static int mapcount = 2;
	static int Chin_HP = 266;
	static int Kap_HP = 266;
	static int timeone = 9;
	static int timeten = 5;
	static int start = 1;
	static int fight = 0;
	static bool ko = FALSE;

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		
		PlaySound(TEXT("02-THE-KING-OF-FIGHTERS-_94-Opening-_MVS-Title_.wav"), NULL, SND_FILENAME | SND_ASYNC);

		ui.UI_img_load();
		for (int i = 0; i < 22; ++i) {
			ui.UIindex[i].ImageInitialize();
		}
		//HPbar
		ui.img_left[HP] = 93;
		ui.img_top[HP] = 20;

		//Chinname
		ui.img_left[CHINNAME] = 173;
		ui.img_top[CHINNAME] = 69;

		//Kapname
		ui.img_left[KAPNAME] = 538;
		ui.img_top[KAPNAME] = 69;

		//Chinprofle
		ui.img_left[CHINPROFILE] = 126;
		ui.img_top[CHINPROFILE] = 40;

		//Kapprofle
		ui.img_left[KAPPROFILE] = 711;
		ui.img_top[KAPPROFILE] = 40;

		//Time
		for (int i = 0; i < 10; i++) {
			ui.img_left[i + 8] = 414;
			ui.img_top[i + 8] = 37;
		}

		effect.Initialize_effect();

		Gen.initialize_chin();
		Gen.img_left = 135;
		Gen.img_top = 332;

		Kap.initialize_kaphwan();
		Kap.img_left = 600;
		Kap.img_top = 300;

		break;

	case WM_TIMER:
		switch (wParam) {
		case 0:
			if (mapcount == 3) {
				mapcount = 2;
			}
			else if (mapcount == 2) {
				mapcount = 3;
			}
			break;

		case 1:
			Gen.standing_chin.goto_next_img();
			Gen.frontmove_chin.goto_next_img();
			Gen.backmove_chin.goto_next_img();
			Gen.sitdown_chin.goto_next_img();
			break;
		case 2:
			if (Gen.condition1 == JUMP && Gen.condition2 == NOATTACK) {
				Gen.jump_chin.goto_next_img();
				if (Gen.jump_chin.ani_index == 11) {
					Gen.condition1 = STANDING;
					Gen.standing_chin.ani_index = 0;
					Gen.jump_chin.ani_index = 0;
					Gen.img_top = 332;
				}
			}
			else if (Gen.condition1 == JUMP && Gen.condition2 == FRONTMOVE) {
				Gen.jump_chin.goto_next_img();
				if (Gen.jump_chin.ani_index == 11) {
					Gen.condition1 = STANDING;
					Gen.standing_chin.ani_index = 0;
					Gen.jump_chin.ani_index = 0;
					Gen.img_top = 332;
				}
			}
			else if (Gen.condition1 == JUMP && Gen.condition2 == BACKMOVE) {
				Gen.jump_chin.goto_next_img();
				if (Gen.jump_chin.ani_index == 11) {
					Gen.condition1 = STANDING;
					Gen.standing_chin.ani_index = 0;
					Gen.jump_chin.ani_index = 0;
					Gen.img_top = 332;
				}
			}
			else if (Gen.condition1 == JUMP && Gen.condition2 == WEAKPUNCH) {
				Gen.jump_chin.goto_next_img();
				if (Gen.jump_chin.ani_index == 11) {
					Gen.condition1 = STANDING;
					Gen.condition2 = NOATTACK;
					Gen.standing_chin.ani_index = 0;
					Gen.jump_chin.ani_index = 0;
					Gen.img_top = 332;

					Gen.jumpsmallpunch_chin.hitbox.left = -1000;
					Gen.jumpsmallpunch_chin.hitbox.top = -1000;
					Gen.jumpsmallpunch_chin.hitbox.right = -1000;
					Gen.jumpsmallpunch_chin.hitbox.bottom = -1000;
				}
			}
			else if (Gen.condition1 == JUMP && Gen.condition2 == STRONGPUNCH) {
				Gen.jump_chin.goto_next_img();
				if (Gen.jump_chin.ani_index == 11) {
					Gen.condition1 = STANDING;
					Gen.condition2 = NOATTACK;
					Gen.standing_chin.ani_index = 0;
					Gen.jump_chin.ani_index = 0;
					Gen.img_top = 332;

					Gen.jumpsmallpunch_chin.hitbox.left = -1000;
					Gen.jumpsmallpunch_chin.hitbox.top = -1000;
					Gen.jumpsmallpunch_chin.hitbox.right = -1000;
					Gen.jumpsmallpunch_chin.hitbox.bottom = -1000;
				}
			}
			else if (Gen.condition1 == JUMP && Gen.condition2 == WEAKKICK) {
				Gen.jump_chin.goto_next_img();
				if (Gen.jump_chin.ani_index == 11) {
					Gen.condition1 = STANDING;
					Gen.condition2 = NOATTACK;
					Gen.standing_chin.ani_index = 0;
					Gen.jump_chin.ani_index = 0;
					Gen.img_top = 332;

					Gen.jumpsmallkick_chin.hitbox.left = -1000;
					Gen.jumpsmallkick_chin.hitbox.top = -1000;
					Gen.jumpsmallkick_chin.hitbox.right = -1000;
					Gen.jumpsmallkick_chin.hitbox.bottom = -1000;
				}
			}
			else if (Gen.condition1 == JUMP && Gen.condition2 == STRONGKICK) {
				Gen.jump_chin.goto_next_img();
				if (Gen.jump_chin.ani_index == 11) {
					Gen.condition1 = STANDING;
					Gen.condition2 = NOATTACK;
					Gen.standing_chin.ani_index = 0;
					Gen.jump_chin.ani_index = 0;
					Gen.img_top = 332;

					Gen.jumpsmallkick_chin.hitbox.left = -1000;
					Gen.jumpsmallkick_chin.hitbox.top = -1000;
					Gen.jumpsmallkick_chin.hitbox.right = -1000;
					Gen.jumpsmallkick_chin.hitbox.bottom = -1000;
				}
			}
			break;
		case 3:
			if (Gen.condition1 == STANDING && Gen.condition2 == WEAKPUNCH) {
				Gen.smallpunch_chin.goto_next_img();
				if (Gen.smallpunch_chin.ani_index == 4) {
					Gen.condition2 = NOATTACK;
					Gen.standing_chin.ani_index = 0;
					Gen.smallpunch_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == SITTING && Gen.condition2 == WEAKPUNCH) {
				Gen.downsmallpunch_chin.goto_next_img();
				if (Gen.downsmallpunch_chin.ani_index == 4) {
					Gen.condition2 = NOATTACK;
					if (!(GetAsyncKeyState(VK_DOWN) & 0x8000)) {
						Gen.condition1 = STANDING;
					}
					if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
						Gen.condition1 = SITTING;
					}
					Gen.sitdown_chin.ani_index = 0;
					Gen.downsmallpunch_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == JUMP && Gen.condition2 == WEAKPUNCH) {
				Gen.jumpsmallpunch_chin.goto_next_img();
				if (Gen.jumpsmallpunch_chin.ani_index == 6) {
					Gen.condition2 = NOATTACK;
					Gen.jumpsmallpunch_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == STANDING && Gen.condition2 == STRONGPUNCH) {
				Gen.bigpunch_chin.goto_next_img();
				if (Gen.bigpunch_chin.ani_index == 6) {
					Gen.condition2 = NOATTACK;
					Gen.standing_chin.ani_index = 0;
					Gen.bigpunch_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == SITTING && Gen.condition2 == STRONGPUNCH) {
				Gen.downsmallpunch_chin.goto_next_img();
				if (Gen.downsmallpunch_chin.ani_index == 4) {
					Gen.condition2 = NOATTACK;
					if (!(GetAsyncKeyState(VK_DOWN) & 0x8000)) {
						Gen.condition1 = STANDING;
					}
					if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
						Gen.condition1 = SITTING;
					}
					Gen.sitdown_chin.ani_index = 0;
					Gen.downsmallpunch_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == JUMP && Gen.condition2 == STRONGPUNCH) {
				Gen.jumpsmallpunch_chin.goto_next_img();
				if (Gen.jumpsmallpunch_chin.ani_index == 6) {
					Gen.condition2 = NOATTACK;
					Gen.jumpsmallpunch_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == STANDING && Gen.condition2 == WEAKKICK) {
				Gen.smallkick_chin.goto_next_img();
				if (Gen.smallkick_chin.ani_index == 5) {
					Gen.condition2 = NOATTACK;
					Gen.standing_chin.ani_index = 0;
					Gen.smallkick_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == SITTING && Gen.condition2 == WEAKKICK) {
				Gen.downsmallkick_chin.goto_next_img();
				if (Gen.downsmallkick_chin.ani_index == 6) {
					Gen.condition2 = NOATTACK;
					if (!(GetAsyncKeyState(VK_DOWN) & 0x8000)) {
						Gen.condition1 = STANDING;
					}
					if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
						Gen.condition1 = SITTING;
					}
					Gen.sitdown_chin.ani_index = 0;
					Gen.downsmallkick_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == JUMP && Gen.condition2 == WEAKKICK) {
				Gen.jumpsmallkick_chin.goto_next_img();
				if (Gen.jumpsmallkick_chin.ani_index == 6) {
					Gen.condition2 = NOATTACK;
					Gen.jumpsmallkick_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == STANDING && Gen.condition2 == STRONGKICK) {
				Gen.bigkick_chin.goto_next_img();
				if (Gen.bigkick_chin.ani_index == 8) {
					Gen.condition2 = NOATTACK;
					Gen.standing_chin.ani_index = 0;
					Gen.bigkick_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == SITTING && Gen.condition2 == STRONGKICK) {
				Gen.downsmallkick_chin.goto_next_img();
				if (Gen.downsmallkick_chin.ani_index == 6) {
					Gen.condition2 = NOATTACK;
					if (!(GetAsyncKeyState(VK_DOWN) & 0x8000)) {
						Gen.condition1 = STANDING;
					}
					if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
						Gen.condition1 = SITTING;
					}
					Gen.sitdown_chin.ani_index = 0;
					Gen.downsmallkick_chin.ani_index = 0;
				}
			}
			if (Gen.condition1 == JUMP && Gen.condition2 == STRONGKICK) {
				Gen.jumpsmallkick_chin.goto_next_img();
				if (Gen.jumpsmallkick_chin.ani_index == 6) {
					Gen.condition2 = NOATTACK;
					Gen.jumpsmallkick_chin.ani_index = 0;
				}
			}
			break;
		case 4:
			if (Gen.condition1 != SITTING) {
				switch (Gen.condition2) {
				case FRONTMOVE:
					if (Gen.img_left > 0) {
						Gen.img_left -= 2;

						Gen.hitbox.left -= 2;
						Gen.hitbox.right -= 2;
					}
					break;
				case BACKMOVE:
					if (Gen.img_left + 140 < WINDOW_WIDTH) {
						Gen.img_left += 3;

						Gen.hitbox.left += 3;
						Gen.hitbox.right += 3;
					}
					break;
				}
			}
			if (Gen.condition1 == JUMP) {
				if (Gen.jump_chin.ani_index == 0) {
					Gen.hitbox.left = Gen.img_left + 13;
					Gen.hitbox.top = Gen.img_top + 22;
					Gen.hitbox.right = Gen.img_left + 95;
					Gen.hitbox.bottom = Gen.img_top + 127;
				}

				if (Gen.jump_chin.ani_index < 5) {
					Gen.img_top -= 10;

					Gen.hitbox.top -= 10;
					Gen.hitbox.bottom -= 10;
				}
				else if (Gen.jump_chin.ani_index > 5) {
					Gen.img_top += 10;

					Gen.hitbox.top += 10;
					Gen.hitbox.bottom += 10;
				}
			}
			break;
		case 5: {
			Kap.standing_kaphwan.goto_next_img();
			Kap.frontmove_kaphwan.goto_next_img();
			Kap.backmove_kaphwan.goto_next_img();
			break;
		}

		case 6: {
			if (Kap.condition1 == JUMP && Kap.condition2 == NOATTACK) {
				Kap.jump_kaphwan.goto_next_img();
				if (Kap.jump_kaphwan.ani_index == 11) {
					Kap.condition1 = STANDING;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.jump_kaphwan.ani_index = 0;
					Kap.img_top = 300;
				}
			}
			else if (Kap.condition1 == JUMP && Kap.condition2 == FRONTMOVE) {
				Kap.jump_kaphwan.goto_next_img();
				if (Kap.jump_kaphwan.ani_index == 11) {
					Kap.condition1 = STANDING;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.jump_kaphwan.ani_index = 0;
					Kap.img_top = 300;
				}
			}
			else if (Kap.condition1 == JUMP && Kap.condition2 == BACKMOVE) {
				Kap.jump_kaphwan.goto_next_img();
				if (Kap.jump_kaphwan.ani_index == 11) {
					Kap.condition1 = STANDING;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.jump_kaphwan.ani_index = 0;
					Kap.img_top = 300;
				}
			}
			else if (Kap.condition1 == JUMP && Kap.condition2 == WEAKPUNCH) {
				Kap.jump_kaphwan.goto_next_img();
				if (Kap.jump_kaphwan.ani_index == 11) {
					Kap.condition1 = STANDING;
					Kap.condition2 = NOATTACK;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.jump_kaphwan.ani_index = 0;
					Kap.img_top = 300;

					Kap.jumppunch_kaphwan.hitbox.left = -1000;
					Kap.jumppunch_kaphwan.hitbox.top = -1000;
					Kap.jumppunch_kaphwan.hitbox.right = -1000;
					Kap.jumppunch_kaphwan.hitbox.bottom = -1000;

					Kap.jumpkick_kaphwan.hitbox.left = -1000;
					Kap.jumpkick_kaphwan.hitbox.top = -1000;
					Kap.jumpkick_kaphwan.hitbox.right = -1000;
					Kap.jumpkick_kaphwan.hitbox.bottom = -1000;
					
				}
			}
			else if (Kap.condition1 == JUMP && Kap.condition2 == STRONGPUNCH) {
				Kap.jump_kaphwan.goto_next_img();
				if (Kap.jump_kaphwan.ani_index == 11) {
					Kap.condition1 = STANDING;
					Kap.condition2 = NOATTACK;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.jump_kaphwan.ani_index = 0;
					Kap.img_top = 300;

					Kap.jumppunch_kaphwan.hitbox.left = -1000;
					Kap.jumppunch_kaphwan.hitbox.top = -1000;
					Kap.jumppunch_kaphwan.hitbox.right = -1000;
					Kap.jumppunch_kaphwan.hitbox.bottom = -1000;

					Kap.jumpkick_kaphwan.hitbox.left = -1000;
					Kap.jumpkick_kaphwan.hitbox.top = -1000;
					Kap.jumpkick_kaphwan.hitbox.right = -1000;
					Kap.jumpkick_kaphwan.hitbox.bottom = -1000;
				}
			}
			else if (Kap.condition1 == JUMP && Kap.condition2 == WEAKKICK) {
				Kap.jump_kaphwan.goto_next_img();
				if (Kap.jump_kaphwan.ani_index == 11) {
					Kap.condition1 = STANDING;
					Kap.condition2 = NOATTACK;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.jump_kaphwan.ani_index = 0;
					Kap.img_top = 300;

					Kap.jumppunch_kaphwan.hitbox.left = -1000;
					Kap.jumppunch_kaphwan.hitbox.top = -1000;
					Kap.jumppunch_kaphwan.hitbox.right = -1000;
					Kap.jumppunch_kaphwan.hitbox.bottom = -1000;

					Kap.jumpkick_kaphwan.hitbox.left = -1000;
					Kap.jumpkick_kaphwan.hitbox.top = -1000;
					Kap.jumpkick_kaphwan.hitbox.right = -1000;
					Kap.jumpkick_kaphwan.hitbox.bottom = -1000;
				}
			}
			else if (Kap.condition1 == JUMP && Kap.condition2 == STRONGKICK) {
				Kap.jump_kaphwan.goto_next_img();
				if (Kap.jump_kaphwan.ani_index == 11) {
					Kap.condition1 = STANDING;
					Kap.condition2 = NOATTACK;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.jump_kaphwan.ani_index = 0;
					Kap.img_top = 300;

					Kap.jumppunch_kaphwan.hitbox.left = -1000;
					Kap.jumppunch_kaphwan.hitbox.top = -1000;
					Kap.jumppunch_kaphwan.hitbox.right = -1000;
					Kap.jumppunch_kaphwan.hitbox.bottom = -1000;

					Kap.jumpkick_kaphwan.hitbox.left = -1000;
					Kap.jumpkick_kaphwan.hitbox.top = -1000;
					Kap.jumpkick_kaphwan.hitbox.right = -1000;
					Kap.jumpkick_kaphwan.hitbox.bottom = -1000;
				}
			}

			break;
		}

		case 7: {
			// 갑환 약펀치
			if (Kap.condition1 == STANDING && Kap.condition2 == WEAKPUNCH) {
				Kap.weakpunch_kaphwan.goto_next_img();
				if (Kap.weakpunch_kaphwan.ani_index == 4) {
					Kap.condition2 = NOATTACK;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.weakpunch_kaphwan.ani_index = 0;
				}
			}
			if (Kap.condition1 == SITTING && Kap.condition2 == WEAKPUNCH) {
				Kap.sittingpunch_kaphwan.goto_next_img();
				if (Kap.sittingpunch_kaphwan.ani_index == 4) {
					Kap.condition2 = NOATTACK;
					if (!(GetAsyncKeyState('Q') & 0x8000)) {
						Kap.condition1 = STANDING;
					}
					if (GetAsyncKeyState('q') & 0x8000) {
						Kap.condition1 = SITTING;
					}
					Kap.sitting_kaphwan.ani_index = 0;
					Kap.sittingpunch_kaphwan.ani_index = 0;
				}
			}
			if (Kap.condition1 == JUMP && Kap.condition2 == WEAKPUNCH) {
				Kap.jumppunch_kaphwan.goto_next_img();
				if (Kap.jumppunch_kaphwan.ani_index == 6) {
					Kap.condition2 = NOATTACK;
					Kap.jumppunch_kaphwan.ani_index = 0;
				}
			}

			//갑환 강펀치
			if (Kap.condition1 == STANDING && Kap.condition2 == STRONGPUNCH) {
				Kap.strongpunch_kaphwan.goto_next_img();
				if (Kap.strongpunch_kaphwan.ani_index == 6) {
					Kap.condition2 = NOATTACK;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.strongpunch_kaphwan.ani_index = 0;
				}
			}
			if (Kap.condition1 == SITTING && Kap.condition2 == STRONGPUNCH) {
				Kap.sittingpunch_kaphwan.goto_next_img();
				if (Kap.sittingpunch_kaphwan.ani_index == 4) {
					Kap.condition2 = NOATTACK;
					if (!(GetAsyncKeyState('Q') & 0x8000)) {
						Kap.condition1 = STANDING;
					}
					if (GetAsyncKeyState('q') & 0x8000) {
						Kap.condition1 = SITTING;
					}
					Kap.sitting_kaphwan.ani_index = 0;
					Kap.sittingpunch_kaphwan.ani_index = 0;
				}
			}
			if (Kap.condition1 == JUMP && Kap.condition2 == STRONGPUNCH) {
				Kap.jumppunch_kaphwan.goto_next_img();
				if (Kap.jumppunch_kaphwan.ani_index == 6) {
					Kap.condition2 = NOATTACK;
					Kap.jumppunch_kaphwan.ani_index = 0;
				}
			}

			// 갑환 약발차기
			if (Kap.condition1 == STANDING && Kap.condition2 == WEAKKICK) {
				Kap.weakkick_kaphwan.goto_next_img();
				if (Kap.weakkick_kaphwan.ani_index == 6) {
					Kap.condition2 = NOATTACK;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.weakkick_kaphwan.ani_index = 0;
				}
			}
			if (Kap.condition1 == SITTING && Kap.condition2 == WEAKKICK) {
				Kap.sittingkick_kaphwan.goto_next_img();
				if (Kap.sittingkick_kaphwan.ani_index == 4) {
					Kap.condition2 = NOATTACK;
					if (!(GetAsyncKeyState('Q') & 0x8000)) {
						Kap.condition1 = STANDING;
					}
					if (GetAsyncKeyState('q') & 0x8000) {
						Kap.condition1 = SITTING;
					}
					Kap.sitting_kaphwan.ani_index = 0;
					Kap.sittingkick_kaphwan.ani_index = 0;
				}
			}
			if (Kap.condition1 == JUMP && Kap.condition2 == WEAKKICK) {
				Kap.jumpkick_kaphwan.goto_next_img();
				if (Kap.jumpkick_kaphwan.ani_index == 6) {
					Kap.condition2 = NOATTACK;
					Kap.jumpkick_kaphwan.ani_index = 0;
				}
			}

			// 갑환 강발차기
			if (Kap.condition1 == STANDING && Kap.condition2 == STRONGKICK) {
				Kap.strongkick_kaphwan.goto_next_img();
				if (Kap.strongkick_kaphwan.ani_index == 8) {
					Kap.condition2 = NOATTACK;
					Kap.standing_kaphwan.ani_index = 0;
					Kap.strongkick_kaphwan.ani_index = 0;
				}
			}
			if (Kap.condition1 == SITTING && Kap.condition2 == STRONGKICK) {
				Kap.sittingkick_kaphwan.goto_next_img();
				if (Kap.sittingkick_kaphwan.ani_index == 4) {
					Kap.condition2 = NOATTACK;
					if (!(GetAsyncKeyState('Q') & 0x8000)) {
						Kap.condition1 = STANDING;
					}
					if (GetAsyncKeyState('q') & 0x8000) {
						Kap.condition1 = SITTING;
					}
					Kap.sitting_kaphwan.ani_index = 0;
					Kap.sittingkick_kaphwan.ani_index = 0;
				}
			}
			if (Kap.condition1 == JUMP && Kap.condition2 == STRONGKICK) {
				Kap.jumpkick_kaphwan.goto_next_img();
				if (Kap.jumpkick_kaphwan.ani_index == 6) {
					Kap.condition2 = NOATTACK;
					Kap.jumpkick_kaphwan.ani_index = 0;
				}
			}

			break;
		}

		case 8: {
			if (Kap.condition1 != SITTING) {
				switch (Kap.condition2) {
				case FRONTMOVE:
					if (Kap.img_left > 0) {
						Kap.img_left -= 3;

						Kap.hitbox.left -= 3;
						Kap.hitbox.right -= 3;
					}
					break;
				case BACKMOVE:
					if (Kap.img_left + 140 < WINDOW_WIDTH) {
						Kap.img_left += 2;

						Kap.hitbox.left += 2;
						Kap.hitbox.right += 2;
					}
					break;
				}
			}

			if (Kap.condition1 == JUMP) {
				if (Kap.jump_kaphwan.ani_index == 0) {
					Kap.hitbox.left = Kap.img_left + 13;
					Kap.hitbox.top = Kap.img_top + 22;
					Kap.hitbox.right = Kap.img_left + 95;
					Kap.hitbox.bottom = Kap.img_top + 147;
				}

				if (Kap.jump_kaphwan.ani_index < 5) {
					Kap.img_top -= 10;

					Kap.hitbox.top -= 10;
					Kap.hitbox.bottom -= 10;
				}
				else if (Kap.jump_kaphwan.ani_index > 5) {
					Kap.img_top += 10;

					Kap.hitbox.top += 10;
					Kap.hitbox.bottom += 10;
				}

				break;
			}

			
			break;
		}

		case 9: {
			// 겐이 피격당했을 경우
			if (Gen.condition3 == HITTED) {
				if (Gen.condition1 == STANDING) {
					Gen.standinghit_chin.goto_next_img();
					if (Gen.standinghit_chin.ani_index == 4) {
						Gen.condition3 = NOHIT;

						Gen.condition1 = STANDING;
						Gen.condition2 = NOATTACK;

						Gen.standing_chin.ani_index = 0;
						Gen.standinghit_chin.ani_index = 0;
					}
				}
				else if (Gen.condition1 == SITTING) {
					Gen.sittinghit_chin.goto_next_img();
					if (Gen.sittinghit_chin.ani_index == 4) {
						Gen.condition3 = NOHIT;

						Gen.condition1 = STANDING;
						Gen.condition2 = NOATTACK;

						Gen.standing_chin.ani_index = 0;
						Gen.sittinghit_chin.ani_index = 0;
					}
				}
				else if (Gen.condition1 == JUMP) {
					Gen.jumphit_chin.goto_next_img();
					if (Gen.jumphit_chin.ani_index < 7) {
						Gen.condition3 = HITTED;
						Gen.condition1 = JUMP;
						Gen.condition2 = NOATTACK;
					}
					else if (Gen.jumphit_chin.ani_index == 7) {
						Gen.condition3 = NOHIT;

						Gen.condition1 = STANDING;
						Gen.condition2 = NOATTACK;

						Gen.img_top = 332;

						Gen.standing_chin.ani_index = 0;
						Gen.jumphit_chin.ani_index = 0;
					}
				}
			}

			else if (Gen.condition3 == GUARD) {
				if (Gen.condition1 == STANDING) {
					Gen.standingguard_chin.goto_next_img();
					if (Gen.standingguard_chin.ani_index == 3) {
						Gen.condition3 = NOHIT;

						Gen.condition1 = STANDING;
						Gen.condition2 = NOATTACK;

						Gen.standing_chin.ani_index = 0;
						Gen.standingguard_chin.ani_index = 0;
					}
				}
				else if (Gen.condition1 == SITTING) {
					Gen.sittingguard_chin.goto_next_img();
					if (Gen.sittingguard_chin.ani_index == 3) {
						Gen.condition3 = NOHIT;

						Gen.condition1 = STANDING;
						Gen.condition2 = NOATTACK;

						Gen.standing_chin.ani_index = 0;
						Gen.sittingguard_chin.ani_index = 0;
					}
				}
			}


			// 갑환 공격당했을 경우
			else if (Kap.condition3 == HITTED) {
				if (Kap.condition1 == STANDING) {
					Kap.standinghit_kaphwan.goto_next_img();
					if (Kap.standinghit_kaphwan.ani_index == 4) {
						Kap.condition3 = NOHIT;

						Kap.condition1 = STANDING;
						Kap.condition2 = NOATTACK;

						Kap.standing_kaphwan.ani_index = 0;
						Kap.standinghit_kaphwan.ani_index = 0;
					}
				}
				else if (Kap.condition1 == SITTING) {
					Kap.sittinghit_kaphwan.goto_next_img();
					if (Kap.sittinghit_kaphwan.ani_index == 4) {
						Kap.condition3 = NOHIT;

						Kap.condition1 = STANDING;
						Kap.condition2 = NOATTACK;

						Kap.standing_kaphwan.ani_index = 0;
						Kap.sittinghit_kaphwan.ani_index = 0;
					}
				}
				else if (Kap.condition1 == JUMP) {
					Kap.jumphit_kaphwan.goto_next_img();
					if (Kap.jumphit_kaphwan.ani_index < 7) {
						Kap.condition3 = HITTED;
						Kap.condition1 = JUMP;
						Kap.condition2 = NOATTACK;
					}
					else if (Kap.jumphit_kaphwan.ani_index == 7) {
						Kap.condition3 = NOHIT;

						Kap.condition1 = STANDING;
						Kap.condition2 = NOATTACK;
						
						Kap.img_top = 300;

						Kap.standing_kaphwan.ani_index = 0;
						Kap.jumphit_kaphwan.ani_index = 0;
					}
				}
			}

			else if (Kap.condition3 == GUARD) {
				if (Kap.condition1 == STANDING) {
					Kap.standingguard_kaphwan.goto_next_img();
					if (Kap.standingguard_kaphwan.ani_index == 3) {
						Kap.condition3 = NOHIT;
						
						Kap.condition1 = STANDING;
						Kap.condition2 = NOATTACK;
					
						Kap.standing_kaphwan.ani_index = 0;
						Kap.standingguard_kaphwan.ani_index = 0;
					}
				}
				else if (Kap.condition1 == SITTING) {
					Kap.sittingguard_kaphwan.goto_next_img();
					if (Kap.sittingguard_kaphwan.ani_index == 3) {
						Kap.condition3 = NOHIT;
						
						Kap.condition1 = STANDING;
						Kap.condition2 = NOATTACK;
					
						Kap.standing_kaphwan.ani_index = 0;
						Kap.sittingguard_kaphwan.ani_index = 0;
					}
				}
			}
			break;
		}

		case 10: {

			// 겐이 갑환의 공격에 맞음 충돌체크
			if (IntersectRect(&hitvoid, &Gen.hitbox, &Kap.weakpunch_kaphwan.hitbox)) {
				if (Gen.condition3 != HITTED) {
					cout << "겐이 약한 손 갑환 공격 맞음" << endl;

					Gen.hitbox.left = -5000;
					Gen.hitbox.top = -5000;
					Gen.hitbox.right = -5000;
					Gen.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;
					
					if (Gen.condition1 == JUMP) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 10;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState(VK_LEFT) & 0x8000)) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 10;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
						Gen.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Gen.hitbox, &Kap.strongpunch_kaphwan.hitbox)) {
				if (Gen.condition3 != HITTED) {
					cout << "겐이 강한 손 갑환 공격 맞음" << endl;

					Gen.hitbox.left = -5000;
					Gen.hitbox.top = -5000;
					Gen.hitbox.right = -5000;
					Gen.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Gen.condition1 == JUMP) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 12;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState(VK_LEFT) & 0x8000)) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 12;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
						Gen.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Gen.hitbox, &Kap.weakkick_kaphwan.hitbox)) {
				if (Gen.condition3 != HITTED) {
					cout << "겐이 약한 발 갑환 공격 맞음" << endl;

					Gen.hitbox.left = -5000;
					Gen.hitbox.top = -5000;
					Gen.hitbox.right = -5000;
					Gen.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Gen.condition1 == JUMP) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 12;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState(VK_LEFT) & 0x8000)) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 12;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
						Gen.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Gen.hitbox, &Kap.strongkick_kaphwan.hitbox)) {
				if (Gen.condition3 != HITTED) {
					cout << "겐이 강한 발 갑환 공격 맞음" << endl;

					Gen.hitbox.left = -5000;
					Gen.hitbox.top = -5000;
					Gen.hitbox.right = -5000;
					Gen.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Gen.condition1 == JUMP) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 15;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState(VK_LEFT) & 0x8000)) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 15;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
						Gen.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}

			if (IntersectRect(&hitvoid, &Gen.hitbox, &Kap.jumppunch_kaphwan.hitbox)) {
				if (Gen.condition3 != HITTED) {
					cout << "겐이 점프 손 갑환 공격 맞음" << endl;

					Gen.hitbox.left = -5000;
					Gen.hitbox.top = -5000;
					Gen.hitbox.right = -5000;
					Gen.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Gen.condition1 == JUMP) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 17;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState(VK_LEFT) & 0x8000)) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 17;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
						Gen.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Gen.hitbox, &Kap.jumpkick_kaphwan.hitbox)) {
				if (Gen.condition3 != HITTED) {
					cout << "겐이 점프 발 갑환 공격 맞음" << endl;

					Gen.hitbox.left = -5000;
					Gen.hitbox.top = -5000;
					Gen.hitbox.right = -5000;
					Gen.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Gen.condition1 == JUMP) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 20;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState(VK_LEFT) & 0x8000)) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 20;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
						Gen.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}

			if (IntersectRect(&hitvoid, &Gen.hitbox, &Kap.sittingpunch_kaphwan.hitbox)) {
				if (Gen.condition3 != HITTED) {
					cout << "겐이 앉아 주먹 갑환 공격 맞음" << endl;

					Gen.hitbox.left = -5000;
					Gen.hitbox.top = -5000;
					Gen.hitbox.right = -5000;
					Gen.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Gen.condition1 == JUMP) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 10;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState(VK_DOWN) & 0x8000)) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 10;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
						Gen.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Gen.hitbox, &Kap.sittingkick_kaphwan.hitbox)) {
				if (Gen.condition3 != HITTED) {
					cout << "겐이 앉아 발 갑환 공격 맞음" << endl;

					Gen.hitbox.left = -5000;
					Gen.hitbox.top = -5000;
					Gen.hitbox.right = -5000;
					Gen.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Gen.condition1 == JUMP) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 12;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState(VK_DOWN) & 0x8000)) {
						Gen.condition3 = HITTED;
						effect.condition = HITTED;
						if (Chin_HP > 0) {
							Chin_HP -= 12;
							if (Chin_HP < 0) Chin_HP = 0;
						}
					}
					else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
						Gen.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}


			// 갑환이 겐의 공격에 맞음 충돌체크
			if (IntersectRect(&hitvoid, &Kap.hitbox, &Gen.smallpunch_chin.hitbox)) {
				if (Kap.condition3 != HITTED) {
					cout << "갑환이 약한 손 겐 공격 맞음" << endl;

					Kap.hitbox.left = -5000;
					Kap.hitbox.top = -5000;
					Kap.hitbox.right = -5000;
					Kap.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Kap.condition1 == JUMP) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 10;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState('W') & 0x8000)) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 10;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (GetAsyncKeyState('W') & 0x8000) {
						Kap.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Kap.hitbox, &Gen.bigpunch_chin.hitbox)) {
				if (Kap.condition3 != HITTED) {
					cout << "갑환이 강한 손 겐 공격 맞음" << endl;

					Kap.hitbox.left = -5000;
					Kap.hitbox.top = -5000;
					Kap.hitbox.right = -5000;
					Kap.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Kap.condition1 == JUMP) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 12;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState('W') & 0x8000)) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 12;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (GetAsyncKeyState('W') & 0x8000) {
						Kap.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Kap.hitbox, &Gen.smallkick_chin.hitbox)) {
				if (Kap.condition3 != HITTED) {
					cout << "갑환이 약한 발 겐 공격 맞음" << endl;

					Kap.hitbox.left = -5000;
					Kap.hitbox.top = -5000;
					Kap.hitbox.right = -5000;
					Kap.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Kap.condition1 == JUMP) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 12;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState('W') & 0x8000)) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 12;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (GetAsyncKeyState('W') & 0x8000) {
						Kap.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Kap.hitbox, &Gen.bigkick_chin.hitbox)) {
				if (Kap.condition3 != HITTED) {
					cout << "갑환이 강한 발 겐 공격 맞음" << endl;

					Kap.hitbox.left = -5000;
					Kap.hitbox.top = -5000;
					Kap.hitbox.right = -5000;
					Kap.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Kap.condition1 == JUMP) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 15;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState('W') & 0x8000)) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 15;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (GetAsyncKeyState('W') & 0x8000) {
						Kap.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}

			if (IntersectRect(&hitvoid, &Kap.hitbox, &Gen.jumpsmallpunch_chin.hitbox)) {
				if (Kap.condition3 != HITTED) {
					cout << "갑환이 점프 손 겐 공격 맞음" << endl;

					Kap.hitbox.left = -5000;
					Kap.hitbox.top = -5000;
					Kap.hitbox.right = -5000;
					Kap.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Kap.condition1 == JUMP) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 17;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState('W') & 0x8000)) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 17;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (GetAsyncKeyState('W') & 0x8000) {
						Kap.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Kap.hitbox, &Gen.jumpsmallkick_chin.hitbox)) {
				if (Kap.condition3 != HITTED) {
					cout << "갑환이 점프 발 겐 공격 맞음" << endl;

					Kap.hitbox.left = -5000;
					Kap.hitbox.top = -5000;
					Kap.hitbox.right = -5000;
					Kap.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Kap.condition1 == JUMP) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 20;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState('W') & 0x8000)) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 20;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (GetAsyncKeyState('W') & 0x8000) {
						Kap.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}

			if (IntersectRect(&hitvoid, &Kap.hitbox, &Gen.downsmallpunch_chin.hitbox)) {
				if (Kap.condition3 != HITTED) {
					cout << "갑환이 앉아 주먹 겐 공격 맞음" << endl;

					Kap.hitbox.left = -5000;
					Kap.hitbox.top = -5000;
					Kap.hitbox.right = -5000;
					Kap.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Kap.condition1 == JUMP) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 10;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState('Q') & 0x8000)) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 10;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (GetAsyncKeyState('Q') & 0x8000) {
						Kap.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (IntersectRect(&hitvoid, &Kap.hitbox, &Gen.downsmallkick_chin.hitbox)) {
				if (Kap.condition3 != HITTED) {
					cout << "갑환이 앉아 발 겐 공격 맞음" << endl;

					Kap.hitbox.left = -5000;
					Kap.hitbox.top = -5000;
					Kap.hitbox.right = -5000;
					Kap.hitbox.bottom = -5000;

					effect.img_left = hitvoid.left;
					effect.img_top = hitvoid.top;
					effect.img_right = hitvoid.right;
					effect.img_bottom = hitvoid.bottom;

					if (Kap.condition1 == JUMP) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 12;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (!(GetAsyncKeyState('Q') & 0x8000)) {
						Kap.condition3 = HITTED;
						effect.condition = HITTED;
						if (Kap_HP > 0) {
							Kap_HP -= 12;
							if (Kap_HP < 0) Kap_HP = 0;
						}
					}
					else if (GetAsyncKeyState('Q') & 0x8000) {
						Kap.condition3 = GUARD;
						effect.condition = GUARD;
					}
				}
			}
			if (Chin_HP == 0 || Kap_HP == 0) {
				ko = TRUE;
				if (Chin_HP == 0) {
					//친
					KillTimer(hWnd, 1);
					KillTimer(hWnd, 2);
					KillTimer(hWnd, 3);
					KillTimer(hWnd, 4);
				}
				if (Kap_HP == 0) {
					//갑환
					KillTimer(hWnd, 5);
					KillTimer(hWnd, 6);
					KillTimer(hWnd, 7);
					KillTimer(hWnd, 8);
				}
				KillTimer(hWnd, 9);
				KillTimer(hWnd, 10);
				KillTimer(hWnd, 11);
				KillTimer(hWnd, 12);
				KillTimer(hWnd, 13);
				PlaySound(TEXT("Announce_Ko.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		}


		case 11: {
			if (effect.condition == HITTED) {
				// 겐사이 맞았을때
				if (Gen.condition3 == HITTED) {
					if (effect.hit.ani_index == 0) {
						PlaySound(TEXT("p05#8"), NULL, SND_FILENAME | SND_ASYNC);
					}
				}

				// 갑환 맞았을때
				if (Kap.condition3 == HITTED) {
					if (effect.hit.ani_index == 0) {
						PlaySound(TEXT("p0c#9"), NULL, SND_FILENAME | SND_ASYNC);
					}
				}

				effect.hit.goto_next_img();

				if (effect.hit.ani_index == 9) {
					effect.hit.ani_index = 0;
					effect.condition = NOHIT;
				}
			}
			else if (effect.condition == GUARD) {
				// 겐사이 가드때
				if (Gen.condition3 == GUARD) {
					if (effect.hit.ani_index == 0) {
						PlaySound(TEXT("p05#7"), NULL, SND_FILENAME | SND_ASYNC);
					}
				}

				// 갑환 가드때
				if (Kap.condition3 == GUARD) {
					if (effect.hit.ani_index == 0) {
						PlaySound(TEXT("p0c#8"), NULL, SND_FILENAME | SND_ASYNC);
					}
				}

				effect.guard.goto_next_img();

				if (effect.guard.ani_index == 9) {
					effect.guard.ani_index = 0;
					effect.condition = NOHIT;
				}
			}

			break;
		}

		case 12:
			fight++;
			if (3 == fight) {
				PlaySound(TEXT("Announce_Fight.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (fight == 5) SetTimer(hWnd, 13, 10000, NULL);
			else if (fight >= 5) {
				if (timeone > 0) timeone--;
				else timeone = 9;
				if (timeone == 0 && timeten == 0) {
					KillTimer(hWnd, 12);
					KillTimer(hWnd, 13);
				}
			}
			break;
		case 13:
			if (fight >= 5) {
				timeten--;
			}
			break;


		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);
		InvalidateRect(hWnd, NULL, FALSE); // 화면에 다시 그리기를 할 때 기존의 내용을 삭제하지 않음
		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_F8:
			if (mode_hitbox) mode_hitbox = false;
			else if (!mode_hitbox) mode_hitbox = true;
			break;
		case 'p':
		case 'P':
			if (start <= 2) {
				start++;
				if (start == 3) {
					//Background
					SetTimer(hWnd, 0, 300, NULL);

					//친
					SetTimer(hWnd, 1, 130, NULL);
					SetTimer(hWnd, 2, 50, NULL);
					SetTimer(hWnd, 3, 80, NULL);
					SetTimer(hWnd, 4, 1, NULL);
					//갑환
					SetTimer(hWnd, 5, 130, NULL);
					SetTimer(hWnd, 6, 50, NULL);
					SetTimer(hWnd, 7, 80, NULL);
					SetTimer(hWnd, 8, 1, NULL);

					// 충돌 후 무적시간 쿨 체크
					SetTimer(hWnd, 9, 50, NULL);
					// 충돌체크 타이머
					SetTimer(hWnd, 10, 1, NULL);
					// 이펙트 타이머
					SetTimer(hWnd, 11, 40, NULL);
					//시간 타이머(1의자리)
					SetTimer(hWnd, 12, 1000, NULL);

					PlaySound(NULL, 0, 0);
					playbackgroundmusic();
				}
			}
			break;

		case VK_LEFT:
			if (fight >= 4) {
				if (Gen.condition3 != NOHIT) break;
				if (Gen.condition1 != SITTING && Gen.condition2 == NOATTACK) {
					if (Gen.condition2 != FRONTMOVE) {
						Gen.condition2 = FRONTMOVE;
						Gen.frontmove_chin.ani_index = 0;
					}
				}
			}
			break;
		case VK_RIGHT:
			if (fight >= 4) {
				if (Gen.condition3 != NOHIT) break;
				if (Gen.condition1 != SITTING && Gen.condition2 == NOATTACK) {
					if (Gen.condition2 != BACKMOVE) {
						Gen.condition2 = BACKMOVE;
						Gen.backmove_chin.ani_index = 0;
					}
				}
			}
			break;
		case VK_UP:
			if (fight >= 4) {
				if (Gen.condition3 != NOHIT) break;
				if (Gen.condition1 == STANDING && Gen.condition2 != WEAKPUNCH && Gen.condition2 != STRONGPUNCH && Gen.condition2 != WEAKKICK && Gen.condition2 != STRONGKICK) {
					if (Gen.condition1 != JUMP) {
						Gen.condition1 = JUMP;
						Gen.jump_chin.ani_index = 0;
					}
				}
			}
			break;
		case VK_DOWN:
			if (fight >= 4) {
				if (Gen.condition3 != NOHIT) break;
				if (Gen.condition1 == STANDING && Gen.condition2 != WEAKPUNCH && Gen.condition2 != STRONGPUNCH && Gen.condition2 != WEAKKICK && Gen.condition2 != STRONGKICK) {
					Gen.condition1 = SITTING;
					Gen.sitdown_chin.ani_index = 0;
					if (Gen.condition2 == FRONTMOVE) {
						Gen.condition1 = SITTING;
						Gen.condition2 = NOATTACK;
					}
					if (Gen.condition2 == BACKMOVE) {
						Gen.condition1 = SITTING;
						Gen.condition2 = NOATTACK;
					}
				}
			}
			break;
		case VK_NUMPAD1:
			if (fight >= 4) {
				if (Gen.condition3 != NOHIT) break;
				if (Gen.condition2 == NOATTACK || Gen.condition2 == FRONTMOVE || Gen.condition2 == BACKMOVE) {
					Gen.condition2 = WEAKPUNCH;
					Gen.smallpunch_chin.ani_index = 0;
					Gen.downsmallpunch_chin.ani_index = 0;
					Gen.jumpsmallpunch_chin.ani_index = 0;
				}
			}
			break;
		case VK_NUMPAD2:
			if (fight >= 4) {
				if (Gen.condition3 != NOHIT) break;
				if (Gen.condition2 == NOATTACK || Gen.condition2 == FRONTMOVE || Gen.condition2 == BACKMOVE) {
					Gen.condition2 = STRONGPUNCH;

					PlaySound(TEXT("p05#6"), NULL, SND_FILENAME | SND_ASYNC);

					Gen.bigpunch_chin.ani_index = 0;
					Gen.downsmallpunch_chin.ani_index = 0;
					Gen.jumpsmallpunch_chin.ani_index = 0;
				}
			}
			break;
		case VK_NUMPAD4:
			if (fight >= 4) {
				if (Gen.condition3 != NOHIT) break;
				if (Gen.condition2 == NOATTACK || Gen.condition2 == FRONTMOVE || Gen.condition2 == BACKMOVE) {
					Gen.condition2 = WEAKKICK;
					Gen.smallkick_chin.ani_index = 0;
					Gen.downsmallkick_chin.ani_index = 0;
					Gen.jumpsmallkick_chin.ani_index = 0;
				}
			}
			break;
		case VK_NUMPAD5:
			if (fight >= 4) {
				if (Gen.condition3 != NOHIT) break;
				if (Gen.condition2 == NOATTACK || Gen.condition2 == FRONTMOVE || Gen.condition2 == BACKMOVE) {
					Gen.condition2 = STRONGKICK;

					PlaySound(TEXT("p05#9"), NULL, SND_FILENAME | SND_ASYNC);

					Gen.smallkick_chin.ani_index = 0;
					Gen.downsmallkick_chin.ani_index = 0;
					Gen.jumpsmallkick_chin.ani_index = 0;
				}
			}
			break;
		}

		switch (wParam) {
		case 'q':
		case 'Q':
			if (fight >= 4) {
				if (Kap.condition3 != NOHIT) break;
				if (Kap.condition1 == STANDING && Kap.condition2 != WEAKPUNCH && Kap.condition2 != STRONGPUNCH && Kap.condition2 != WEAKKICK && Kap.condition2 != STRONGKICK) {
					Kap.condition1 = SITTING;
					Kap.sitting_kaphwan.ani_index = 0;
					if (Kap.condition2 == FRONTMOVE || Kap.condition2 == BACKMOVE) {
						Kap.condition2 = NOATTACK;
					}
				}
			}
			break;
		case VK_TAB:
			if (fight >= 4) {
				if (Kap.condition3 != NOHIT) break;
				if (Kap.condition1 != SITTING && Kap.condition2 == NOATTACK) {
					if (Kap.condition2 != FRONTMOVE) {
						Kap.condition2 = FRONTMOVE;
						Kap.frontmove_kaphwan.ani_index = 0;
					}
				}
			}
			break;
		case 'w':
		case 'W':
			if (fight >= 4) {
				if (Kap.condition3 != NOHIT) break;
				if (Kap.condition1 != SITTING && Kap.condition2 == NOATTACK) {
					if (Kap.condition2 != BACKMOVE) {
						Kap.condition2 = BACKMOVE;
						Kap.backmove_kaphwan.ani_index = 0;
					}
				}
			}
			break;
		case '1':
			if (fight >= 4) {
				if (Kap.condition3 != NOHIT) break;
				if (Kap.condition1 == STANDING && Kap.condition2 != WEAKPUNCH && Kap.condition2 != STRONGPUNCH && Kap.condition2 != WEAKKICK && Kap.condition2 != STRONGKICK) {
					if (Kap.condition1 != JUMP) {
						Kap.condition1 = JUMP;
						Kap.jump_kaphwan.ani_index = 0;
					}
				}
			}
			break;
		case 't':
		case 'T':
			if (fight >= 4) {
				if (Kap.condition3 != NOHIT) break;
				if (Kap.condition2 == NOATTACK || Kap.condition2 == FRONTMOVE || Kap.condition2 == BACKMOVE) {
					Kap.condition2 = WEAKPUNCH;
					Kap.weakpunch_kaphwan.ani_index = 0;
					Kap.sittingpunch_kaphwan.ani_index = 0;
					Kap.jumppunch_kaphwan.ani_index = 0;
				}
			}
			break;
		case 'y':
		case 'Y':
			if (fight >= 4) {
				if (Kap.condition3 != NOHIT) break;
				if (Kap.condition2 == NOATTACK || Kap.condition2 == FRONTMOVE || Kap.condition2 == BACKMOVE) {
					Kap.condition2 = STRONGPUNCH;

					PlaySound(TEXT("p0c#11"), NULL, SND_FILENAME | SND_ASYNC);

					Kap.strongpunch_kaphwan.ani_index = 0;
					Kap.sittingpunch_kaphwan.ani_index = 0;
					Kap.jumppunch_kaphwan.ani_index = 0;
				}
			}
			break;
		case '5':
			if (fight >= 4) {
				if (Kap.condition3 != NOHIT) break;
				if (Kap.condition2 == NOATTACK || Kap.condition2 == FRONTMOVE || Kap.condition2 == BACKMOVE) {
					Kap.condition2 = WEAKKICK;
					Kap.weakkick_kaphwan.ani_index = 0;
					Kap.sittingkick_kaphwan.ani_index = 0;
					Kap.jumpkick_kaphwan.ani_index = 0;
				}
			}
			break;
		case '6':
			if (fight >= 4) {
				if (Kap.condition3 != NOHIT) break;
				if (Kap.condition2 == NOATTACK || Kap.condition2 == FRONTMOVE || Kap.condition2 == BACKMOVE) {
					Kap.condition2 = STRONGKICK;

					PlaySound(TEXT("p0c#5"), NULL, SND_FILENAME | SND_ASYNC);

					Kap.strongkick_kaphwan.ani_index = 0;
					Kap.sittingkick_kaphwan.ani_index = 0;
					Kap.jumpkick_kaphwan.ani_index = 0;
				}
			}
			break;
		}


		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYUP:
		hDC = GetDC(hWnd);

		switch (wParam) {
		case VK_LEFT:
			if (Gen.condition2 != WEAKPUNCH && Gen.condition2 != STRONGPUNCH && Gen.condition2 != WEAKKICK && Gen.condition2 != STRONGKICK) {
				Gen.condition2 = NOATTACK;
				Gen.standing_chin.ani_index = 0;
			}
			break;
		case VK_RIGHT:
			if (Gen.condition2 != WEAKPUNCH && Gen.condition2 != STRONGPUNCH && Gen.condition2 != WEAKKICK && Gen.condition2 != STRONGKICK) {
				Gen.condition2 = NOATTACK;
				Gen.standing_chin.ani_index = 0;
			}
			break;
		case VK_DOWN:
			if (Gen.condition2 == NOATTACK) {
				if (Gen.condition1 != JUMP) {
					Gen.condition1 = STANDING;
					Gen.standing_chin.ani_index = 0;
				}
			}
			break;
		}

		if (wParam == 'q' || wParam == 'Q') {
			if (Kap.condition2 == NOATTACK) {
				if (Kap.condition1 != JUMP) {
					Kap.condition1 = STANDING;
					Kap.standing_kaphwan.ani_index = 0;
				}
			}
		}
		else if (wParam == VK_TAB) {
			if (Kap.condition2 != WEAKPUNCH && Kap.condition2 != STRONGPUNCH && Kap.condition2 != WEAKKICK && Kap.condition2 != STRONGKICK) {
				Kap.condition2 = NOATTACK;
				Kap.standing_kaphwan.ani_index = 0;
			}
		}
		else if (wParam == 'w' || wParam == 'W') {
			if (Kap.condition2 != WEAKPUNCH && Kap.condition2 != STRONGPUNCH && Kap.condition2 != WEAKKICK && Kap.condition2 != STRONGKICK) {
				Kap.condition2 = NOATTACK;
				Kap.standing_kaphwan.ani_index = 0;
			}
		}

		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap); //--- 메모리 DC와 비트맵 연결하기
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- 화면에 비어있기 때문에 화면 가득히 사각형을 그려 배경색으로 설정하기


		// Background
		ui.UIindex[MAP1_1].img.StretchBlt(mDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ui.UIindex[MAP1_1].img_width, ui.UIindex[MAP1_1].img_height);
		if (mapcount == 2) {
			ui.UIindex[MAP1_2].img.TransparentBlt(mDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ui.UIindex[MAP1_2].img_width, ui.UIindex[MAP1_2].img_height, RGB(255, 192, 255));
		}
		if (mapcount == 3) {
			ui.UIindex[MAP1_3].img.TransparentBlt(mDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ui.UIindex[MAP1_3].img_width, ui.UIindex[MAP1_3].img_height, RGB(255, 192, 255));
		}

		//----친
		if (Gen.condition1 == STANDING) {
			switch (Gen.condition3) {
			case NOHIT:
				switch (Gen.condition2) {
				case NOATTACK:
					Gen.print_standing_chin(mDC);
					break;
				case FRONTMOVE:
					Gen.print_frontmove_chin(mDC);
					break;
				case BACKMOVE:
					Gen.print_backmove_chin(mDC);
					break;
				case WEAKPUNCH:
					Gen.print_smallpunch_chin(mDC);
					break;
				case STRONGPUNCH:
					Gen.print_bigpunch_chin(mDC);
					break;
				case WEAKKICK:
					Gen.print_smallkick_chin(mDC);
					break;
				case STRONGKICK:
					Gen.print_bigkick_chin(mDC);
					break;
				}
				break;

			case HITTED:
				Gen.print_standinghit_chin(mDC);
				break;
			case GUARD:
				Gen.print_standingguard_chin(mDC);
				break;
			}
		}

		else if (Gen.condition1 == JUMP) {
			switch (Gen.condition3) {
			case NOHIT:
				switch (Gen.condition2) {
				case NOATTACK:
					Gen.print_jump_chin(mDC);
					break;
				case FRONTMOVE:
					Gen.print_jump_chin(mDC);
					break;
				case BACKMOVE:
					Gen.print_jump_chin(mDC);
					break;
				case WEAKPUNCH:
					Gen.print_jumpsmallpunch_chin(mDC);
					break;
				case STRONGPUNCH:
					Gen.print_jumpsmallpunch_chin(mDC);
					break;
				case WEAKKICK:
					Gen.print_jumpsmallkick_chin(mDC);
					break;
				case STRONGKICK:
					Gen.print_jumpsmallkick_chin(mDC);
					break;
				}
				break;

			case HITTED:
				Gen.print_jumphit_chin(mDC);
				break;
			}
		}

		else if (Gen.condition1 == SITTING) {
			switch (Gen.condition3) {
			case NOHIT:
				switch (Gen.condition2) {
				case NOATTACK:
					Gen.print_sitdown_chin(mDC);
					break;
				case WEAKPUNCH:
					Gen.print_downsmallpunch_chin(mDC);
					break;
				case STRONGPUNCH:
					Gen.print_downsmallpunch_chin(mDC);
					break;
				case WEAKKICK:
					Gen.print_downsmallkick_chin(mDC);
					break;
				case STRONGKICK:
					Gen.print_downsmallkick_chin(mDC);
					break;
				}
				break;

			case HITTED:
				Gen.print_sittinghit_chin(mDC);
				break;
			case GUARD:
				Gen.print_sittingguard_chin(mDC);
				break;
			}
		}

		//----갑환
		if (Kap.condition1 == STANDING) {
			switch (Kap.condition3) {
			case NOHIT:
				switch (Kap.condition2) {
				case NOATTACK:
					Kap.print_standing_kaphwan(mDC);
					break;
				case FRONTMOVE:
					Kap.print_frontmove_kaphwan(mDC);
					break;
				case BACKMOVE:
					Kap.print_backmove_kaphwan(mDC);
					break;
				case WEAKPUNCH:
					Kap.print_weakpunch_kaphwan(mDC);
					break;
				case STRONGPUNCH:
					Kap.print_strongpunch_kaphwan(mDC);
					break;
				case WEAKKICK:
					Kap.print_weakkick_kaphwan(mDC);
					break;
				case STRONGKICK:
					Kap.print_strongkick_kaphwan(mDC);
					break;
				}
				break;

			case HITTED:
				Kap.print_standinghit_kaphwan(mDC);
				break;
			case GUARD:
				Kap.print_standingguard_kaphwan(mDC);
				break;
			}
		}

		else if (Kap.condition1 == JUMP) {
			switch (Kap.condition3) {
			case NOHIT:
				switch (Kap.condition2) {
				case NOATTACK:
					Kap.print_jump_kaphwan(mDC);
					break;
				case FRONTMOVE:
					Kap.print_jump_kaphwan(mDC);
					break;
				case BACKMOVE:
					Kap.print_jump_kaphwan(mDC);
					break;
				case WEAKPUNCH:
					Kap.print_jumppunch_kaphwan(mDC);
					break;
				case STRONGPUNCH:
					Kap.print_jumppunch_kaphwan(mDC);
					break;
				case WEAKKICK:
					Kap.print_jumpkick_kaphwan(mDC);
					break;
				case STRONGKICK:
					Kap.print_jumpkick_kaphwan(mDC);
				}
				break;
				
			case HITTED:
				Kap.print_jumphit_kaphwan(mDC);
				break;
			}
		}

		else if (Kap.condition1 == SITTING) {
			switch (Kap.condition3) {
			case NOHIT:
				switch (Kap.condition2) {
				case NOATTACK:
					Kap.print_sitting_kaphwan(mDC);
					break;
				case WEAKPUNCH:
					Kap.print_sittingpunch_kaphwan(mDC);
					break;
				case STRONGPUNCH:
					Kap.print_sittingpunch_kaphwan(mDC);
					break;
				case WEAKKICK:
					Kap.print_sittingkick_kaphwan(mDC);
					break;
				case STRONGKICK:
					Kap.print_sittingkick_kaphwan(mDC);
					break;
				}
				break;

			case HITTED:
				Kap.print_sittinghit_kaphwan(mDC);
				break;
			case GUARD:
				Kap.print_sittingguard_kaphwan(mDC);
				break;
			}
		}

		if (effect.condition == HITTED) {
			effect.print_hit(mDC);
		}
		else if (effect.condition == GUARD) {
			effect.print_guard(mDC);
		}


		if (mode_hitbox) {
			// 겐사이
			draw_framerectangle(mDC, Gen.hitbox.left, Gen.hitbox.top, Gen.hitbox.right, Gen.hitbox.bottom, RGB(0, 0, 255));

			draw_framerectangle(mDC, Gen.smallpunch_chin.hitbox.left, Gen.smallpunch_chin.hitbox.top, Gen.smallpunch_chin.hitbox.right, Gen.smallpunch_chin.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Gen.bigpunch_chin.hitbox.left, Gen.bigpunch_chin.hitbox.top, Gen.bigpunch_chin.hitbox.right, Gen.bigpunch_chin.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Gen.smallkick_chin.hitbox.left, Gen.smallkick_chin.hitbox.top, Gen.smallkick_chin.hitbox.right, Gen.smallkick_chin.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Gen.bigkick_chin.hitbox.left, Gen.bigkick_chin.hitbox.top, Gen.bigkick_chin.hitbox.right, Gen.bigkick_chin.hitbox.bottom, RGB(255, 0, 0));

			draw_framerectangle(mDC, Gen.jumpsmallpunch_chin.hitbox.left, Gen.jumpsmallpunch_chin.hitbox.top, Gen.jumpsmallpunch_chin.hitbox.right, Gen.jumpsmallpunch_chin.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Gen.jumpsmallkick_chin.hitbox.left, Gen.jumpsmallkick_chin.hitbox.top, Gen.jumpsmallkick_chin.hitbox.right, Gen.jumpsmallkick_chin.hitbox.bottom, RGB(255, 0, 0));

			draw_framerectangle(mDC, Gen.downsmallpunch_chin.hitbox.left, Gen.downsmallpunch_chin.hitbox.top, Gen.downsmallpunch_chin.hitbox.right, Gen.downsmallpunch_chin.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Gen.downsmallkick_chin.hitbox.left, Gen.downsmallkick_chin.hitbox.top, Gen.downsmallkick_chin.hitbox.right, Gen.downsmallkick_chin.hitbox.bottom, RGB(255, 0, 0));

			// 갑환
			draw_framerectangle(mDC, Kap.hitbox.left, Kap.hitbox.top, Kap.hitbox.right, Kap.hitbox.bottom, RGB(0, 0, 255));

			draw_framerectangle(mDC, Kap.weakpunch_kaphwan.hitbox.left, Kap.weakpunch_kaphwan.hitbox.top, Kap.weakpunch_kaphwan.hitbox.right, Kap.weakpunch_kaphwan.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Kap.strongpunch_kaphwan.hitbox.left, Kap.strongpunch_kaphwan.hitbox.top, Kap.strongpunch_kaphwan.hitbox.right, Kap.strongpunch_kaphwan.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Kap.weakkick_kaphwan.hitbox.left, Kap.weakkick_kaphwan.hitbox.top, Kap.weakkick_kaphwan.hitbox.right, Kap.weakkick_kaphwan.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Kap.strongkick_kaphwan.hitbox.left, Kap.strongkick_kaphwan.hitbox.top, Kap.strongkick_kaphwan.hitbox.right, Kap.strongkick_kaphwan.hitbox.bottom, RGB(255, 0, 0));

			draw_framerectangle(mDC, Kap.jumppunch_kaphwan.hitbox.left, Kap.jumppunch_kaphwan.hitbox.top, Kap.jumppunch_kaphwan.hitbox.right, Kap.jumppunch_kaphwan.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Kap.jumpkick_kaphwan.hitbox.left, Kap.jumpkick_kaphwan.hitbox.top, Kap.jumpkick_kaphwan.hitbox.right, Kap.jumpkick_kaphwan.hitbox.bottom, RGB(255, 0, 0));

			draw_framerectangle(mDC, Kap.sittingpunch_kaphwan.hitbox.left, Kap.sittingpunch_kaphwan.hitbox.top, Kap.sittingpunch_kaphwan.hitbox.right, Kap.sittingpunch_kaphwan.hitbox.bottom, RGB(255, 0, 0));
			draw_framerectangle(mDC, Kap.sittingkick_kaphwan.hitbox.left, Kap.sittingkick_kaphwan.hitbox.top, Kap.sittingkick_kaphwan.hitbox.right, Kap.sittingkick_kaphwan.hitbox.bottom, RGB(255, 0, 0));
		}


		// HPbar
		ui.img_right[HP] = ui.img_left[HP] + ui.UIindex[HP].img_width;
		ui.img_bottom[HP] = ui.img_top[HP] + ui.UIindex[HP].img_height;
		ui.UIindex[HP].img.TransparentBlt(mDC, ui.img_left[HP], ui.img_top[HP], ui.img_right[HP] - ui.img_left[HP] + 450, ui.img_bottom[HP] - ui.img_top[HP] + 50, 0, 0, ui.UIindex[HP].img_width, ui.UIindex[HP].img_height, RGB(0, 0, 32));

		// Chin_name
		ui.img_right[CHINNAME] = ui.img_left[CHINNAME] + ui.UIindex[CHINNAME].img_width;
		ui.img_bottom[CHINNAME] = ui.img_top[CHINNAME] + ui.UIindex[CHINNAME].img_height;
		ui.UIindex[CHINNAME].img.TransparentBlt(mDC, ui.img_left[CHINNAME], ui.img_top[CHINNAME], ui.img_right[CHINNAME] - ui.img_left[CHINNAME], ui.img_bottom[CHINNAME] - ui.img_top[CHINNAME], 0, 0, ui.UIindex[CHINNAME].img_width, ui.UIindex[CHINNAME].img_height, RGB(57, 81, 57));

		// Kap_name
		ui.img_right[KAPNAME] = ui.img_left[KAPNAME] + ui.UIindex[KAPNAME].img_width;
		ui.img_bottom[KAPNAME] = ui.img_top[KAPNAME] + ui.UIindex[KAPNAME].img_height;
		ui.UIindex[KAPNAME].img.TransparentBlt(mDC, ui.img_left[KAPNAME], ui.img_top[KAPNAME], ui.img_right[KAPNAME] - ui.img_left[KAPNAME], ui.img_bottom[KAPNAME] - ui.img_top[KAPNAME], 0, 0, ui.UIindex[KAPNAME].img_width, ui.UIindex[KAPNAME].img_height, RGB(57, 81, 57));

		// Chin_profile
		ui.img_right[CHINPROFILE] = ui.img_left[CHINPROFILE] + ui.UIindex[CHINPROFILE].img_width;
		ui.img_bottom[CHINPROFILE] = ui.img_top[CHINPROFILE] + ui.UIindex[CHINPROFILE].img_height;
		ui.UIindex[CHINPROFILE].img.StretchBlt(mDC, ui.img_left[CHINPROFILE], ui.img_top[CHINPROFILE], ui.img_right[CHINPROFILE] - ui.img_left[CHINPROFILE], ui.img_bottom[CHINPROFILE] - ui.img_top[CHINPROFILE], 0, 0, ui.UIindex[CHINPROFILE].img_width, ui.UIindex[CHINPROFILE].img_height);

		// Kap_profile
		ui.img_right[KAPPROFILE] = ui.img_left[KAPPROFILE] + ui.UIindex[KAPPROFILE].img_width;
		ui.img_bottom[KAPPROFILE] = ui.img_top[KAPPROFILE] + ui.UIindex[KAPPROFILE].img_height;
		ui.UIindex[KAPPROFILE].img.StretchBlt(mDC, ui.img_left[KAPPROFILE], ui.img_top[KAPPROFILE], ui.img_right[KAPPROFILE] - ui.img_left[KAPPROFILE], ui.img_bottom[KAPPROFILE] - ui.img_top[KAPPROFILE], 0, 0, ui.UIindex[KAPPROFILE].img_width, ui.UIindex[KAPPROFILE].img_height);

		// Chin_HP
		draw_rectangle(mDC, 176, 49, 442 - Chin_HP, 67, RGB(255, 0, 0));
		// Kap_HP
		draw_rectangle(mDC, 708, 49, 442 + Kap_HP, 67, RGB(255, 0, 0));

		// Time
		ui.img_right[timeten + 8] = ui.img_left[timeten + 8] + ui.UIindex[timeten + 8].img_width;
		ui.img_bottom[timeten + 8] = ui.img_top[timeten + 8] + ui.UIindex[timeten + 8].img_height;
		ui.UIindex[timeten + 8].img.TransparentBlt(mDC, ui.img_left[timeten + 8], ui.img_top[timeten + 8], ui.img_right[timeten + 8] - ui.img_left[timeten + 8] + 20, ui.img_bottom[timeten + 8] - ui.img_top[timeten + 8] + 30, 0, 0, ui.UIindex[timeten + 8].img_width, ui.UIindex[timeten + 8].img_height, RGB(57, 81, 57));

		ui.img_right[timeone + 8] = ui.img_left[timeone + 8] + ui.UIindex[timeone + 8].img_width;
		ui.img_bottom[timeone + 8] = ui.img_top[timeone + 8] + ui.UIindex[timeone + 8].img_height;
		ui.UIindex[timeone + 8].img.TransparentBlt(mDC, ui.img_left[timeone + 8] + 28, ui.img_top[timeone + 8], ui.img_right[timeone + 8] - ui.img_left[timeone + 8] + 20, ui.img_bottom[timeone + 8] - ui.img_top[timeone + 8] + 30, 0, 0, ui.UIindex[timeone + 8].img_width, ui.UIindex[timeone + 8].img_height, RGB(57, 81, 57));

		//Start
		if (start == 1) {
			ui.UIindex[START1].img.StretchBlt(mDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ui.UIindex[START1].img_width + 10, ui.UIindex[START1].img_height + 31);
		}
		if (start == 2) {
			ui.UIindex[START2].img.StretchBlt(mDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ui.UIindex[START2].img_width + 10, ui.UIindex[START2].img_height + 31);
		}

		//Fight
		if (2 <= fight && fight <= 3) {
			ui.img_right[FIGHT] = ui.img_left[FIGHT] + ui.UIindex[FIGHT].img_width;
			ui.img_bottom[FIGHT] = ui.img_top[FIGHT] + ui.UIindex[FIGHT].img_height;
			ui.UIindex[FIGHT].img.TransparentBlt(mDC, ui.img_left[FIGHT] + 350, ui.img_top[FIGHT] + 200, ui.img_right[FIGHT] - ui.img_left[FIGHT] + 140, ui.img_bottom[FIGHT] - ui.img_top[FIGHT] + 70, 0, 0, ui.UIindex[FIGHT].img_width, ui.UIindex[FIGHT].img_height, RGB(0, 0, 32));
		}

		//KO
		if (ko) {
			ui.img_right[KO] = ui.img_left[KO] + ui.UIindex[KO].img_width;
			ui.img_bottom[KO] = ui.img_top[KO] + ui.UIindex[KO].img_height;
			ui.UIindex[KO].img.TransparentBlt(mDC, ui.img_left[KO] + 365, ui.img_top[KO] + 200, ui.img_right[KO] - ui.img_left[KO] + 140, ui.img_bottom[KO] - ui.img_top[KO] + 70, 0, 0, ui.UIindex[KO].img_width, ui.UIindex[KO].img_height, RGB(0, 0, 32));
			//PlaySound(TEXT("Announce_Ko.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}


		//----


		//--- 마지막에 메모리 DC의 내용을 화면 DC로 복사한다.
		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC); //--- 생성한 메모리 DC 삭제
		DeleteObject(hBitmap); //--- 생성한 비트맵 삭제

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void draw_framerectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	RECT rt{ x1, y1, x2, y2 };
	FrameRect(mDC, &rt, hBrush);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기
	HPEN hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	Rectangle(mDC, x1, y1, x2, y2);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}

void playbackgroundmusic() {
	// 배경음악 파일을 엽니다.
	MCIERROR mciError = mciSendString(TEXT("open \"06-Hey_-_England-Stage_.wav\" type mpegvideo alias bgm"), NULL, 0, NULL);
	if (mciError != 0) {
		TCHAR errorText[128];
		mciGetErrorString(mciError, errorText, sizeof(errorText) / sizeof(TCHAR));
		std::cerr << "MCI open error: " << errorText << std::endl;
		return;
	}

	// 배경음악을 재생합니다.
	mciError = mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
	if (mciError != 0) {
		TCHAR errorText[128];
		mciGetErrorString(mciError, errorText, sizeof(errorText) / sizeof(TCHAR));
		std::cerr << "MCI play error: " << errorText << std::endl;
		mciSendString(TEXT("close bgm"), NULL, 0, NULL); // 에러 발생 시 파일 닫기
		return;
	}
}

