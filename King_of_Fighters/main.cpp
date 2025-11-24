#include "headers.h"
#include "game_manager.h"
#include "draw.h"
#include "NetworkModule.h"

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

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"KOF";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

GAMEMANAGER game_manager;
SESSION session;

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
	static int Chin_HP = 266;
	static int Kap_HP = 266;

	switch (iMessage) {
	case WM_CREATE:
		game_manager.startMusic.playSound();

		//effect.Initialize_effect();
		//
		//Gen.initialize_chin();
		//Gen.img_left = 135;
		//Gen.img_top = 332;
		//
		//Kap.initialize_kaphwan();
		//Kap.img_left = 600;
		//Kap.img_top = 300;

		break;

	case WM_TIMER:
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);
		InvalidateRect(hWnd, NULL, FALSE);
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
			if (game_manager.start <= 2) {
				game_manager.start++;
				if (game_manager.start == 3) {
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
					game_manager.playbackgroundmusic();
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

		session.send_input_packet();
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

		session.send_input_packet();
		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap); //--- 메모리 DC와 비트맵 연결하기
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- 화면에 비어있기 때문에 화면 가득히 사각형을 그려 배경색으로 설정하기

		// Map
		game_manager.printMap(hDC);

		// HPbar
		game_manager.ui.HP._right = game_manager.ui.HP._left + game_manager.ui.HP._width;
		game_manager.ui.HP._bottom = game_manager.ui.HP._top + game_manager.ui.HP._height;
		game_manager.ui.HP._img.TransparentBlt(mDC, game_manager.ui.HP._left, game_manager.ui.HP._top, game_manager.ui.HP._right - game_manager.ui.HP._left + 450, game_manager.ui.HP._bottom - game_manager.ui.HP._top + 50, 0, 0, game_manager.ui.HP._width, game_manager.ui.HP._height, RGB(0, 0, 32));

		// Name
		game_manager.printName(hDC);

		// Profile
		game_manager.printProfile(hDC);

		// Time
		game_manager.printTime(hDC);

		//Start
		game_manager.printStart(hDC);

		//Fight
		game_manager.printFight(hDC);

		//KO
		game_manager.printKO(hDC);

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