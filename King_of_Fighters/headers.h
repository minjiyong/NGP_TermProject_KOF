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
//#include "IMAGE.h"
//#include "Chin.h"
//#include "Kaphwan.h"
//#include "Effect.h"
//#include "UI.h"
//
//#include "NetworkModule.h"
#include "protocol.h"

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[%s] %s\n", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// 소켓 함수 오류 출력
void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[오류] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

static bool recv_exact(SOCKET s, void* p, int len) {
	// 자료형의	크기만큼 정확히 받기
	char* c = (char*)p; int got = 0;
	while (got < len) {
		int n = recv(s, c + got, len - got, 0);
		if (n <= 0) return false;
		got += n;
	}
	return true;
}

static bool send_exact(SOCKET s, const void* p, int len) {
	// 자료형의 크기만큼 정확히 전송
	const char* c = (const char*)p;
	int sent = 0;
	while (sent < len) {
		int n = send(s, c + sent, len - sent, 0);
		if (n == SOCKET_ERROR) return false;
		sent += n;
	}
	return true;
}

bool send_packet(SOCKET s, const void* p) {
	const unsigned char* buf = reinterpret_cast<const unsigned char*>(p);
	unsigned char size = buf[0];

	// 1) 길이 검증 (최소 2: size+type, 최대 BUF_SIZE)
	if (size < 2 || size > BUF_SIZE) return false;

	// 2) 정확히 size 바이트 전송
	send_exact(s, buf, size);
	return true;
}

static bool recv_packet(SOCKET s, void* p) {
	unsigned char size = 0;
	if (!recv_exact(s, &size, 1)) return false;
	if (size < 2 || size > BUF_SIZE) return false;

	char* buf = reinterpret_cast<char*>(p);
	buf[0] = size;

	// 나머지 (size - 1) 바이트 받기
	if (!recv_exact(s, buf + 1, size - 1)) return false;
	return true;
}