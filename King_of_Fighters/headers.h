#pragma once

#define _CRT_SECURE_NO_WARNINGS // 구형 C 함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 구형 소켓 API 사용 시 경고 끄기

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <array>
#include <memory>
#include <TCHAR.H>
#include <ctime>
#include <atlImage.h>
#include "protocol.h"

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg);

// 소켓 함수 오류 출력
void err_display(const char* msg);

// 소켓 함수 오류 출력
void err_display(int errcode);

bool recv_exact(SOCKET s, void* p, int len);

bool send_exact(SOCKET s, const void* p, int len);

bool send_packet(SOCKET s, const void* p);

bool recv_packet(SOCKET s, void* p);