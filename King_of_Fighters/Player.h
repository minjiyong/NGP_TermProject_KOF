#pragma once
#include "headers.h"


class Player
{
public:
	Player();
	~Player();
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
						x_pos = p->x; y_pos = p->y;
					}
					break;
				}
				default: 
				}
			}
			else {
				connected = false;
				break;
			}
		}
	}
private:
	float hp{ 0 };
	int id{};
	int x_pos{ 0 };
	int y_pos{ 0 };
	bool connected;

	P_MOVE_STATE	m_state;
	P_ATTACK_STATE	a_state;
	P_GUARD_STATE	g_state;
	P_HIT_STATE		h_state;

	SOCKET client_socket;
	std::thread _recv_thread;
	char _recv_buf[BUF_SIZE];

	
};


Player::Player()
{
}

Player::~Player()
{
}