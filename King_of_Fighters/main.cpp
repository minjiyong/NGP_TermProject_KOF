#include "headers.h"
#include "game_manager.h"
#include "draw.h"
#include "NetworkModule.h"
#include "chin.h"

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"KOF";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

GAMEMANAGER game_manager;
SESSION session;
std::thread network_thread;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow) {
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

	InitialzeNetwork(session);

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

	static int fight = 5;

	switch (iMessage) {
		case WM_CREATE:
		{
			game_manager.init();
			game_manager.startMusic.playSound();

			for (Chin& player : session._players) {
				player.init();
			}

			//effect.Initialize_effect();

			break;
		}
		case WM_TIMER:
		{
			break;
		}
		case WM_KEYDOWN:
		{
			hDC = GetDC(hWnd);

			for (Chin& chin : session._players) {
				if (chin._id == session._id) {
					switch (wParam) {
						case VK_ESCAPE:
						{
							PostQuitMessage(0);
							break;
						}
						case VK_F9:
						{
							if (mode_hitbox) mode_hitbox = false;
							else if (!mode_hitbox) mode_hitbox = true;
							break;
						}
						case 'p':
						case 'P':
						{
							if (game_manager.start <= 2) {
								game_manager.start++;
								if (game_manager.start == 3) {
									//Background
									SetTimer(hWnd, 0, 300, NULL);

									//// 충돌 후 무적시간 쿨 체크
									//SetTimer(hWnd, 9, 50, NULL);
									//// 충돌체크 타이머
									//SetTimer(hWnd, 10, 1, NULL);
									//// 이펙트 타이머
									//SetTimer(hWnd, 11, 40, NULL);
									////시간 타이머(1의자리)
									//SetTimer(hWnd, 12, 1000, NULL);

									PlaySound(NULL, 0, 0);
									game_manager.playbackgroundmusic();
								}
							}
							break;
						}
						case 'a':
						case 'A':
						{
							if (fight >= 4) {
								if (chin.p_state != PS_ForwardMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_ForwardMove;
								}
							}
							break;
						}
						case 'd':
						case 'D':
						{
							if (fight >= 4) {
								if (chin.p_state != PS_BackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_BackMove;
								}
							}
							break;
						}
						case 'w':
						case 'W':
						{
							if (fight >= 4) {
								// 일어나 있는 상태에서만 점프 가능하도록 함
								//if (chin.p_state == Idle || chin.p_state == ForwardMove || chin.p_state == BackMove) {
								if (chin.p_state != PS_JumpIdle && chin.p_state != PS_JumpForwardMove
									&& chin.p_state != PS_JumpBackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_JumpIdle;
								}
							}
							break;
						}
						case 's':
						case 'S':
						{
							if (fight >= 4) {
								if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_CrouchIdle;
								}
							}
							break;
						}
						case 'j':
						case 'J':
						{
							if (fight >= 4) {
								if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_punch_weak;
								}
								else if (chin.p_state != PS_JumpIdle && chin.p_state != PS_JumpForwardMove && chin.p_state != PS_JumpBackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_punch_jump;
								}
								else if (chin.p_state = PS_CrouchIdle) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_punch_crouch;
								}
							}
							break;
						}
						case 'k':
						case 'K':
						{
							if (fight >= 4) {
								if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_punch_strong;
									PlaySound(TEXT("p05#6"), NULL, SND_FILENAME | SND_ASYNC);
								}
								else if (chin.p_state != PS_JumpIdle && chin.p_state != PS_JumpForwardMove && chin.p_state != PS_JumpBackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_punch_jump;
								}
								else if (chin.p_state = PS_CrouchIdle) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_punch_crouch;
								}
							}
							break;
						}
						case 'n':
						case 'N':
						{
							if (fight >= 4) {
								if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_kick_weak;
								}
								else if (chin.p_state != PS_JumpIdle && chin.p_state != PS_JumpForwardMove && chin.p_state != PS_JumpBackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_kick_jump;
								}
								else if (chin.p_state = PS_CrouchIdle) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_kick_crouch;
								}
							}
							break;
						}
						case 'm':
						case 'M':
						{
							if (fight >= 4) {
								if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_kick_strong;
									PlaySound(TEXT("p05#9"), NULL, SND_FILENAME | SND_ASYNC);
								}
								else if (chin.p_state != PS_JumpIdle && chin.p_state != PS_JumpForwardMove && chin.p_state != PS_JumpBackMove) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_kick_jump;
								}
								else if (chin.p_state = PS_CrouchIdle) {
									std::lock_guard <std::mutex> l_g{ session._lock };
									chin.p_state = PS_kick_crouch;
								}
							}
							break;
						}
					}

					session.send_input_packet(chin);
				}
			}
			InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

			ReleaseDC(hWnd, hDC);
			break;
		}
		case WM_KEYUP:
		{
			hDC = GetDC(hWnd);
			//for (Chin& player : session._players) {
			//	if (player._id == session._id) {
			//		switch (wParam) {
			//		case VK_LEFT:
			//		{
			//			player.p_state = PS_Idle;
			//			break;
			//		}
			//		case VK_RIGHT:
			//		{
			//			player.p_state = PS_Idle;
			//			break;
			//		}
			//		case VK_DOWN:
			//		{
			//			player.p_state = PS_Idle;x
			//			break;
			//		}
			//		}
			//		session.send_input_packet(player);
			//	}
			//}
			//
			InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

			ReleaseDC(hWnd, hDC);
			break;
		}
		case WM_PAINT:
		{
			hDC = BeginPaint(hWnd, &ps);
			mDC = CreateCompatibleDC(hDC); //--- 메모리 DC 만들기
			hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
			SelectObject(mDC, (HBITMAP)hBitmap); //--- 메모리 DC와 비트맵 연결하기
			Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- 화면에 비어있기 때문에 화면 가득히 사각형을 그려 배경색으로 설정하기

			// Map
			game_manager.printMap(mDC);
			
			// HPbar
			game_manager.ui.HP._right = game_manager.ui.HP._left + game_manager.ui.HP._width;
			game_manager.ui.HP._bottom = game_manager.ui.HP._top + game_manager.ui.HP._height;
			game_manager.ui.HP._img.TransparentBlt(mDC, game_manager.ui.HP._left, game_manager.ui.HP._top, game_manager.ui.HP._right - game_manager.ui.HP._left + 450, game_manager.ui.HP._bottom - game_manager.ui.HP._top + 50, 0, 0, game_manager.ui.HP._width, game_manager.ui.HP._height, RGB(0, 0, 32));
			
			// Name
			game_manager.printName(mDC);
			
			// Profile
			game_manager.printProfile(mDC);
			
			//// Time
			//game_manager.printTime(mDC);
			//
			//Start
			game_manager.printStart(mDC);
			
			//Fight
			game_manager.printFight(mDC);
			
			//KO
			game_manager.printKO(mDC);
			
			for (Chin& player : session._players) {
				if (player._id != -1) {
					player.print(mDC);
				}
			}

			//--- 마지막에 메모리 DC의 내용을 화면 DC로 복사한다.
			BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
			DeleteDC(mDC); //--- 생성한 메모리 DC 삭제
			DeleteObject(hBitmap); //--- 생성한 비트맵 삭제

			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			return 0;
		}
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}