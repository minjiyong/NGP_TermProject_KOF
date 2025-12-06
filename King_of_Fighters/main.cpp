#include "headers.h"
#include "game_manager.h"
#include "draw.h"
#include "NetworkModule.h"
#include "chin.h"

#define TIMER_BACKGROUND 0
#define TIMER_TIMEONE 1
#define TIMER_TIMETEN 2
#define TIMER_GAMEOVER 3

#define MAX_HP 532

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

	InitialzeNetwork(session, hWnd);

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
	static int Chin_HP = 333;
	static int Kap_HP = MAX_HP;
	static int fight = 5;
	static bool is_login = false;

	static TCHAR GetID[8] = { '\0' }; static int   id_len = 0;

	switch (iMessage) {
	case WM_CREATE:
	{
		game_manager.init();
		//game_manager.startMusic.playSound();

		for (Chin& player : session._players) {
			player.init();
		}

		//effect.Initialize_effect();

		break;
	}
	case WM_TIMER:
	{
		switch (wParam) {
			// background 타이머
		case TIMER_BACKGROUND:
		{
			if (game_manager.mapTimer == 0) {
				game_manager.mapTimer = 1;
			}
			else if (game_manager.mapTimer == 1) {
				game_manager.mapTimer = 0;
			}
		}
		break;

		// 시간 타이머 - 1의 자리 수 
		case TIMER_TIMEONE:
		{
			game_manager.fight++;
			if (game_manager.fight == 3) {
				PlaySound(TEXT("character\\sound\\Announce_Fight.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (game_manager.fight == 5) SetTimer(hWnd, TIMER_TIMETEN, 10000, NULL);
			else if (game_manager.fight >= 5) {
				if (game_manager.timeone > 0) game_manager.timeone--;
				else game_manager.timeone = 9;
				if (game_manager.timeone == 0 && game_manager.timeten == 0) {
					KillTimer(hWnd, TIMER_BACKGROUND);
					KillTimer(hWnd, TIMER_TIMEONE);
					KillTimer(hWnd, TIMER_TIMETEN);
				}
			}
		}
		break;

		// 시간 타이머 - 10의 자리 수
		case TIMER_TIMETEN:
		{
			if (game_manager.fight >= 5) {
				game_manager.timeten--;
			}
		}
		break;

		// 게임종료 타이머
		case TIMER_GAMEOVER:
		{
			// KO 출력, HP 박스 디버깅용
			//Chin_HP -= 2;

			// 플레이어 발맞추기
			//for (Chin& player : session._players) {
			//	if (player.y_pos < 140) player.y_pos = 332;
			//}

			if (Chin_HP == 0 || Kap_HP == 0) {
				game_manager.ko = TRUE;
				KillTimer(hWnd, 0);
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				PlaySound(TEXT("character\\sound\\Announce_Ko.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}

		}
		break;
	}
	case WM_CHAR:
	{
		if (session._state == ST_CONNECT && is_login)
		{
			TCHAR ch = static_cast<TCHAR>(wParam);

			if (ch == L'\r') // Enter
			{
				if (id_len > 0)
				{
					char send_id[8] = {};   // 서버에 보낼 ANSI 버퍼

					// 유니코드(TCHAR, wchar_t) -> 멀티바이트(char) 변환
					WideCharToMultiByte(
						CP_ACP,             // 코드 페이지 (그냥 시스템 기본)
						0,
						GetID,              // 원본 wide 문자열
						-1,                 // 널까지 변환
						send_id,            // 목적지 버퍼
						sizeof(send_id),    // 버퍼 크기
						NULL, NULL
					);

					session.send_name_info_packet(send_id);
				}
			}
			else if (ch == L'\b') //BackSpace
			{
				// 한 글자 지우기
				if (id_len > 0)
				{
					--id_len;
					GetID[id_len] = L'\0';
				}
			}
			else
			{
				// 여기는 일반 문자 입력 처리
				// 예: 숫자/알파벳만 허용, 길이 7까지만
				if (id_len < 7)  // 마지막은 널 문자
				{
					// 필요하면 조건 추가: isalnum(ch) 같은 것
					GetID[id_len++] = ch;
					GetID[id_len] = L'\0';
				}
			}

			// 입력할 때마다 다시 그리기
			InvalidateRect(hWnd, nullptr, FALSE);
		}
		break;
	}
	case WM_KEYDOWN:
	{
		switch (session._state)
		{
		case ST_CONNECT:
			if (wParam == 'P' || wParam == 'p')
			{
				is_login = true;

			}
			else
			{
				return 0;
			}
			break;
			//if (game_manager.start <= 2) {
			//	game_manager.start++;
			//	if (game_manager.start == 3) {
			//		//Background
			//		SetTimer(hWnd, TIMER_BACKGROUND, 300, NULL);

			//		//// 충돌 후 무적시간 쿨 체크
			//		//SetTimer(hWnd, 9, 50, NULL);
			//		//// 충돌체크 타이머
			//		//SetTimer(hWnd, 10, 1, NULL);
			//		//// 이펙트 타이머
			//		//SetTimer(hWnd, 11, 40, NULL);
			//		//시간 타이머(1의자리)
			//		SetTimer(hWnd, 1, 1000, NULL);

			//		// 게임종료 체크
			//		SetTimer(hWnd, TIMER_GAMEOVER, 100, NULL);

			//		PlaySound(NULL, 0, 0);
			//		//game_manager.playbackgroundmusic();
			//	}
			//}
			
		case ST_INGAME:
			// 게임 진행 중일 때만 입력 처리
			for (Chin& chin : session._players) {
				if (chin._id == session._id) {
					Chin temp = chin;
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
					case 'd':
					case 'D':
					{
						if (fight >= 4) {
							if (chin.p_state != PS_ForwardMove) {
								temp.p_state = PS_ForwardMove;
								session.send_input_packet(temp);
							}
						}
						break;
					}
					case 'a':
					case 'A':
					{
						if (fight >= 4) {
							if (chin.p_state != PS_BackMove) {
								temp.p_state = PS_BackMove;
								session.send_input_packet(temp);
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
							if (chin.p_state != PS_JumpIdle) {
								temp.p_state = PS_JumpIdle;
								session.send_input_packet(temp);
							}
						}
						break;
					}
					case 's':
					case 'S':
					{
						if (fight >= 4) {
							if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
								temp.p_state = PS_CrouchIdle;
								session.send_input_packet(temp);
							}
						}
						break;
					}
					case 'j':
					case 'J':
					{
						if (fight >= 4) {
							if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
								temp.p_state = PS_punch_weak;
								session.send_input_packet(temp);
							}
							else if (chin.p_state == PS_JumpIdle) {
								temp.p_state = PS_punch_jump;
								session.send_input_packet(temp);
							}
							else if (chin.p_state == PS_CrouchIdle) {
								temp.p_state = PS_punch_crouch;
								session.send_input_packet(temp);
							}
						}
						break;
					}
					case 'k':
					case 'K':
					{
						if (fight >= 4) {
							if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
								temp.p_state = PS_punch_strong;
								session.send_input_packet(temp);
								PlaySound(TEXT("character\\sound\\p05#6"), NULL, SND_FILENAME | SND_ASYNC);
							}
							else if (chin.p_state == PS_JumpIdle) {
								temp.p_state = PS_punch_jump;
								session.send_input_packet(temp);
							}
							else if (chin.p_state == PS_CrouchIdle) {
								temp.p_state = PS_punch_crouch;
								session.send_input_packet(temp);
							}
						}
						break;
					}
					case 'n':
					case 'N':
					{
						if (fight >= 4) {
							if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
								temp.p_state = PS_kick_weak;
								session.send_input_packet(temp);
							}
							else if (chin.p_state == PS_JumpIdle) {
								temp.p_state = PS_kick_jump;
								session.send_input_packet(temp);
							}
							else if (chin.p_state == PS_CrouchIdle) {
								temp.p_state = PS_kick_crouch;
								session.send_input_packet(temp);
							}
						}
						break;
					}
					case 'm':
					case 'M':
					{
						if (fight >= 4) {
							if (chin.p_state == PS_Idle || chin.p_state == PS_ForwardMove || chin.p_state == PS_BackMove) {
								temp.p_state = PS_kick_strong;
								session.send_input_packet(temp);
								PlaySound(TEXT("character\\sound\\p05#9"), NULL, SND_FILENAME | SND_ASYNC);
							}
							else if (chin.p_state == PS_JumpIdle) {
								temp.p_state = PS_kick_jump;
								session.send_input_packet(temp);
							}
							else if (chin.p_state == PS_CrouchIdle) {
								temp.p_state = PS_kick_crouch;
								session.send_input_packet(temp);
							}
						}
						break;
					}
					}
				}
			}
			break;
		default:
			break;
		}
		break;
	}
	case WM_KEYUP:
	{
		for (Chin& chin : session._players) {
			Chin temp = chin;
			if (chin._id == session._id) {
				switch (wParam) {
				case 'a':
				case 'A':
				{
					temp.p_state = PS_Idle;
					session.send_input_packet(temp);
					break;
				}
				case 'd':
				case 'D':
				{
					temp.p_state = PS_Idle;
					session.send_input_packet(temp);
					break;
				}
				case 's':
				case 'S':
				{
					temp.p_state = PS_Idle;
					session.send_input_packet(temp);
					break;
				}
				}
			}
		}
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

		switch (session._state) {
		case ST_FREE:
			break;
		case ST_CONNECT:
			//Start
			game_manager.printStart(mDC);

			//Login Box
			if (is_login) {
				RECT box = { 200, 150, 600, 260 };
				HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
				FillRect(mDC, &box, brush);
				SetTextColor(mDC, RGB(255, 255, 255));
				SetBkMode(mDC, TRANSPARENT);

				const TCHAR* title = L"ENTER YOUR ID";
				TextOut(mDC, box.left + 20, box.top + 20, title, lstrlen(title));

				TCHAR buf[32];
				wsprintf(buf, L"ID: %s", GetID);
				TextOut(mDC, box.left + 20, box.top + 60, buf, lstrlen(buf));

				const TCHAR* hint = L"[Enter] 확정 / [Backspace] 지우기 / [ESC] 종료";
				TextOut(mDC, box.left + 20, box.top + 100, hint, lstrlen(hint));
				DeleteObject(brush);
			}
			break;
		case ST_WAITGAME:
		{
			game_manager.printStart(mDC);

			SetTextColor(mDC, RGB(255, 0, 255));
			SetBkMode(mDC, TRANSPARENT);
			TCHAR buf[32] = {};

			for (PLAYER& player : session._players) {
				if (player._id == session._id) {

					// 1) player._name (char[]) -> wide 문자열로 변환
					WCHAR wide_name[16] = {};
					MultiByteToWideChar(
						CP_ACP,
						0,
						player._name,   // char*
						-1,
						wide_name,      // wchar_t*
						16
					);

					// 2) wide_name을 이용해 출력 문자열 만들기
					wsprintf(buf, L"ID: %s", wide_name);
					break;
				}
			}

			TextOut(mDC, 10, 10, buf, lstrlen(buf));
			break;
		}
		case ST_INGAME:
			// Chin
			for (Chin& player : session._players) {
				if (player._id != -1) {
					player.print(mDC);
				}
			}

			// HPbar - P1
			game_manager.ui.HP._right = game_manager.ui.HP._left + game_manager.ui.HP._width;
			game_manager.ui.HP._bottom = game_manager.ui.HP._top + game_manager.ui.HP._height;
			game_manager.ui.HP._img.TransparentBlt(mDC, game_manager.ui.HP._left, game_manager.ui.HP._top, game_manager.ui.HP._right - game_manager.ui.HP._left + 450, game_manager.ui.HP._bottom - game_manager.ui.HP._top + 50, 0, 0, game_manager.ui.HP._width, game_manager.ui.HP._height, RGB(0, 0, 32));

			// HPbar - P2
			game_manager.ui.HP._right = game_manager.ui.HP._left + game_manager.ui.HP._width;
			game_manager.ui.HP._bottom = game_manager.ui.HP._top + game_manager.ui.HP._height;
			game_manager.ui.HP._img.TransparentBlt(mDC, game_manager.ui.HP._left, game_manager.ui.HP._top + 50, game_manager.ui.HP._right - game_manager.ui.HP._left + 450, game_manager.ui.HP._bottom - game_manager.ui.HP._top + 50, 0, 0, game_manager.ui.HP._width, game_manager.ui.HP._height, RGB(0, 0, 32));

			// HPbar - P3
			game_manager.ui.HP._right = game_manager.ui.HP._left + game_manager.ui.HP._width;
			game_manager.ui.HP._bottom = game_manager.ui.HP._top + game_manager.ui.HP._height;
			game_manager.ui.HP._img.TransparentBlt(mDC, game_manager.ui.HP._left, game_manager.ui.HP._top + 100, game_manager.ui.HP._right - game_manager.ui.HP._left + 450, game_manager.ui.HP._bottom - game_manager.ui.HP._top + 50, 0, 0, game_manager.ui.HP._width, game_manager.ui.HP._height, RGB(0, 0, 32));

			// Name
			game_manager.printName(mDC);

			// Profile
			game_manager.printProfile(mDC);

			// Player HP
			game_manager.printHp(mDC, Chin_HP, Chin_HP, Chin_HP);	// p3 HP

			// Time
			game_manager.printTime(mDC);

			//Fight
			game_manager.printFight(mDC);

			//KO
			game_manager.printKO(mDC);
			break;
		case ST_OUTGAME:
			break;
		case ST_DISCONNECT:
			break;
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


