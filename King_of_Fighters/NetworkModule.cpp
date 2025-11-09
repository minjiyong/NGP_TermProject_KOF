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

extern HWND		hWnd;

const static int MAX_TEST = 3;
const static int MAX_CLIENTS = MAX_TEST * 2;
const static int INVALID_ID = -1;
const static int MAX_BUFF_SIZE = 200;

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

#include "protocol.h"

atomic_int num_connections;
atomic_int client_to_close;
atomic_int active_clients;
atomic_int match_clients;

struct CLIENT;

static std::atomic_bool g_use_random{ false };


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

bool NetworkConnected() {
	return (num_connections > 0) && g_clients[0].connected;
}

void SendInputToServer(P_MOVE_STATE m, P_ATTACK_STATE a,
	P_GUARD_STATE g, P_HIT_STATE h)
{
	if (!NetworkConnected()) return;
	CS_INPUT_PACKET p{};
	p.size = sizeof(p);
	p.type = CS_INPUT;
	p.m_state = m;
	p.a_state = a;
	p.g_state = g;
	p.h_state = h;
	send_packet(g_clients[0].client_socket, &p); // 정확히 size바이트 전송
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
					active_clients++;
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
				default: MessageBox(hWnd, L"Unknown Packet Type", L"ERROR", 0);
					while (true);
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

array<CLIENT, MAX_CLIENTS> g_clients;

thread test_thread;
thread print_thread;

void error_display(const char* msg, int err_no)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	std::cout << msg;
	std::wcout << L"에러" << lpMsgBuf << std::endl;

	MessageBox(hWnd, lpMsgBuf, L"ERROR", 0);
	LocalFree(lpMsgBuf);
	// while (true);
}

void DisconnectClient(int ci)
{
	bool status = true;
	if (true == atomic_compare_exchange_strong(&g_clients[ci].connected, &status, false)) {
		closesocket(g_clients[ci].client_socket);
		active_clients--;
	}
	// cout << "Client [" << ci << "] Disconnected!\n";
}

void Adjust_Number_Of_Client()
{
	if (num_connections >= MAX_TEST) return;

	g_clients[num_connections].client_socket = socket(AF_INET, SOCK_STREAM, 0);

	std::cout << "Connecting Client [" << num_connections << "]\n";

	struct sockaddr_in ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &ServerAddr.sin_addr);
	ServerAddr.sin_port = htons(GAME_PORT);

	int Result = connect(g_clients[num_connections].client_socket, (sockaddr*)&ServerAddr, sizeof(ServerAddr));
	if (0 != Result) {
		error_display("onnect : ", GetLastError());
		closesocket(g_clients[num_connections].client_socket);
		return; // 연결 실패 시 조기 복귀 (쓰레드/전송 금지)
	}

	std::cout << "Client [" << num_connections << "] Connected!\n";

	g_clients[num_connections]._recv_thread =
		std::thread(&CLIENT::recv_thread, &g_clients[num_connections]);
	g_clients[num_connections]._recv_thread.detach();

	CS_LOGIN_PACKET p;

	int temp = num_connections;
	sprintf_s(p.name, "%d", (int)num_connections); // 안전
	p.size = sizeof(CS_LOGIN_PACKET);
	p.type = CS_LOGIN;

	send_packet(g_clients[num_connections].client_socket, &p);
	num_connections++;
}

void Test_Thread()
{
	while (true) {
		Adjust_Number_Of_Client();

		for (int i = 0; i < num_connections; ++i) {
			{
				CS_INPUT_PACKET my_packet;
				my_packet.size = sizeof(my_packet);
				my_packet.type = CS_INPUT;
				my_packet.m_state = static_cast<P_MOVE_STATE>((rand() % 9));
				my_packet.a_state = static_cast<P_ATTACK_STATE>((rand() % 5));
				my_packet.g_state = static_cast<P_GUARD_STATE>((rand() % 3));
				my_packet.h_state = static_cast<P_HIT_STATE>((rand() % 3));
				send_packet(g_clients[i].client_socket, &my_packet);
			}
		}
		Sleep(2000);
	}
}

void Print_Thread()
{
	while(true) {
		//for (auto& client : g_clients) {
		//	if (client.connected) {
		//		client.print();
		//	}
		//}
		//Sleep(1000);
		//system("cls");
	}
}

void InitializeNetwork()
{
	for (auto& cl : g_clients) {
		cl.connected = false;
		cl.id = INVALID_ID;
		cl.client_socket = INVALID_SOCKET;
		cl._recv_buf[0] = 0;
		cl.m_state = PMS_NONE;
		cl.a_state = PAS_NONE;
		cl.h_state = PHS_NONE;
		cl.g_state = PGS_NONE;
	}

	num_connections = 0;
	active_clients = 0;
	match_clients = 0;
	client_to_close = 0;

	WSADATA	wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	Adjust_Number_Of_Client();
	g_use_random = false;
	//worker_thread = thread{ Worker_Thread };
	//test_thread = thread{Test_Thread};
	//print_thread = thread{ Print_Thread };
}

void ShutdownNetwork()
{
	for (int i = 0; i < num_connections; ++i) {
		if (g_clients[i].connected) closesocket(g_clients[i].client_socket);
	}
	WSACleanup();
	//test_thread.join();
	//print_thread.join();
	//worker_thread.join();
}

void Do_Network()
{
	return;
}