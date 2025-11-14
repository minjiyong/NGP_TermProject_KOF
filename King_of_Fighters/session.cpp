#include "session.h"

void SESSION::print() {
	for(const PLAYER& p : _players) {
		std::cout << "------------------------" << std::endl;
		std::cout << "Session ID: " << p._id << std::endl;
		std::cout << "m_state: " << (int)p.m_state << std::endl;
		std::cout << "a_state: " << (int)p.a_state << std::endl;
		std::cout << "g_state: " << (int)p.g_state << std::endl;
		std::cout << "h_state: " << (int)p.h_state << std::endl;
	}
	std::cout << "------------------------" << std::endl;
}

void SESSION::send_input_packet() {
	CS_INPUT_PACKET p;
	p.size = sizeof(CS_INPUT_PACKET);
	p.type = CS_INPUT;
	p.m_state = _players[0].m_state;
	p.a_state = _players[0].a_state;
	p.g_state = _players[0].g_state;
	p.h_state = _players[0].h_state;

	send_packet(_socket, &p);
}

void SESSION::recv_thread() {
	while (true) {
		if (_socket == 0) break;
		if (recv_packet(_socket, &_recv_buf)) {
			char* packet = _recv_buf;
			switch (packet[1]) {
			case SC_LOGIN_INFO:
			{
				SC_LOGIN_INFO_PACKET* p = reinterpret_cast<SC_LOGIN_INFO_PACKET*>(packet);
				for(PLAYER& pl : _players) {
					if (!pl.connected) {
						pl._id = p->id;
						pl.connected = true;
						break;
					}
				}
				break;
			}
			case SC_LOGOUT_INFO:
			{
				SC_LOGOUT_INFO_PACKET* p = reinterpret_cast<SC_LOGOUT_INFO_PACKET*>(packet);
				for(PLAYER& pl : _players) {
					if (pl._id == p->id) {
						pl.erase();
						break;
					}
				}
				break;
			}
			case SC_UPDATE:
			{
				SC_UPDATE_PACKET* p = reinterpret_cast<SC_UPDATE_PACKET*>(packet);
				for (PLAYER& pl : _players) {
					if (pl._id == p->id) {
						pl.m_state = p->m_state;
						pl.a_state = p->a_state;
						pl.g_state = p->g_state;
						pl.h_state = p->h_state;
						pl.x_pos = p->x; pl.y_pos = p->y;
						break;
					}
				}
				break;
			}
			default:
			}
		}
		else {
			std::cout << "Client disconnected. ID: " << _players[0]._id << std::endl;
			_players[0].connected = false;
			break;
		}
	}
}