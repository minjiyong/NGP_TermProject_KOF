#pragma once
#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...
#include <string.h> // strncpy(), ...

#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <chrono>

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

#include "protocol.h"
#include "Action.h"
#include "Player.h"	

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

bool recv_exact(SOCKET s, void* p, int len) {
	char* c = reinterpret_cast<char*>(p);
	int got = 0;
	while (got < len) {
		int n = recv(s, c + got, len - got, 0);
		if (n <= 0) return false; // 0=FIN, <0=에러
		got += n;
	}
	return true;
}

bool send_exact(SOCKET s, const void* p, int len) {
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

bool recv_packet(SOCKET s, void* p) {
	unsigned char size = 0;
	if (!recv_exact(s, &size, sizeof(unsigned char))) return false;
	if (size < 2 || size > BUF_SIZE) return false;

	char* buf = reinterpret_cast<char*>(p);
	buf[0] = size;

	// 나머지 (size - 1) 바이트 받기
	if (!recv_exact(s, buf + 1, size - 1)) return false;
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