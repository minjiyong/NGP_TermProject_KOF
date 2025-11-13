#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <Windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include <unordered_set>
#include <mutex>
#include <atomic>
#include <chrono>
#include <queue>
#include <array>
#include <memory>
#include <concurrent_queue.h>

using namespace std;
using namespace chrono;

extern HWND		hWnd = NULL;

const static int MAX_TEST = 3;
const static int MAX_CLIENTS = MAX_TEST * 2;
const static int INVALID_ID = -1;
const static int MAX_BUFF_SIZE = 200;

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

#include "protocol.h"


struct CLIENT;

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

struct CLIENT {
	int id;
	int x;
	int y;
	P_MOVE_STATE	m_state;
	P_ATTACK_STATE	a_state;
	P_GUARD_STATE	g_state;
	P_HIT_STATE		h_state;
	atomic_bool connected;

	SOCKET client_socket;
	std::thread _recv_thread;
	char _recv_buf[BUF_SIZE];

	void print() {
		std::cout << "------------------------" << std::endl;
		std::cout << "Session ID: " << id << std::endl;
		std::cout << "m_state: " << (int)m_state << std::endl;
		std::cout << "a_state: " << (int)a_state << std::endl;
		std::cout << "g_state: " << (int)g_state << std::endl;
		std::cout << "h_state: " << (int)h_state << std::endl;
		std::cout << "------------------------" << std::endl;
	}

	void recv_thread() {
		while (true) {
			if (client_socket == 0) break;
			if (recv_packet(client_socket, &_recv_buf)) {
				char* packet = _recv_buf;
				switch (packet[1]) {
				case SC_LOGIN_INFO:
				{
					connected = true;
					SC_LOGIN_INFO_PACKET* p = reinterpret_cast<SC_LOGIN_INFO_PACKET*>(packet);
					id = p->id;
					break;
				}
				case SC_LOGOUT_INFO:
				{
					connected = false;
					SC_LOGOUT_INFO_PACKET* p = reinterpret_cast<SC_LOGOUT_INFO_PACKET*>(packet);
					id = INVALID_ID;
					break;
				}
				case SC_UPDATE:
				{
					SC_UPDATE_PACKET* p = reinterpret_cast<SC_UPDATE_PACKET*>(packet);
					if (id == p->id) {
						m_state = p->m_state;
						a_state = p->a_state;
						g_state = p->g_state;
						h_state = p->h_state;
						x = p->x; y = p->y;
					}
					break;
				}
				default:
				}
			}
			else {
				std::cout << "Client disconnected. ID: " << id << std::endl;
				connected = false;
				break;
			}
		}
	}
};


extern SOCKET g_sock;

// 서버로 전송하는 함수
void SendInputToServer(P_MOVE_STATE m, P_ATTACK_STATE a, P_GUARD_STATE g, P_HIT_STATE h)
{
	CS_INPUT_PACKET pkt{};
	pkt.size = static_cast<unsigned char>(sizeof(CS_INPUT_PACKET));
	pkt.type = CS_INPUT;
	pkt.m_state = m;
	pkt.a_state = a;
	pkt.g_state = g;
	pkt.h_state = h;

	const char* buf = reinterpret_cast<const char*>(&pkt);
	int total = 0;
	int len = pkt.size;

	while (total < len) {
		int ret = send(g_sock, buf + total, len - total, 0);
		if (ret == SOCKET_ERROR || ret == 0) {
			// int err = WSAGetLastError();
			break;
		}
		total += ret;
	}
}