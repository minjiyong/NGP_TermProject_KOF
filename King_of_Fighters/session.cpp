#include "session.h"

void SESSION::print() {
	std::cout << "------------------------" << std::endl;
	std::cout << "session ID: " << _id << std::endl;
	std::cout << "Session State: " << (int)_state << std::endl;
	for(const PLAYER& p : _players) {
		std::cout << "------------------------" << std::endl;
		std::cout << "Session ID: " << p._id << std::endl;
		std::cout << "Name: " << p._name << std::endl;
		std::cout << "m_state: " << (int)p.p_state << std::endl;
		std::cout << "ani_index: " << p.ani_index << std::endl;
	}
	std::cout << "------------------------" << std::endl;
}

void SESSION::send_login_packet() {
	CS_LOGIN_PACKET p;
	p.size = sizeof(CS_LOGIN_PACKET);
	p.type = CS_LOGIN;
	send_packet(_socket, &p);
}

void SESSION::send_name_info_packet(const char* s_name) {
	CS_NAME_INFO_PACKET p;
	p.size = sizeof(CS_NAME_INFO_PACKET);
	p.type = CS_NAME_INFO;
	strcpy(p.name, s_name);
	send_packet(_socket, &p);
}

void SESSION::send_input_packet(Chin& chin) {
	CS_INPUT_PACKET p;
	p.size = sizeof(CS_INPUT_PACKET);
	p.type = CS_INPUT;
	p.p_state = chin.p_state;
	send_packet(_socket, &p);
}

void SESSION::start_network() {
	_recv_thread = std::thread(&SESSION::recv_thread, this);
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
				std::lock_guard <std::mutex> l_g{ _lock };
				_id = p->id;
				_state = p->s_state;
				_connected = true;

				std::cout << "SC_LOGIN_INFO received. Assigned ID: " << _id << std::endl;
				send_name_info_packet("test1");
				break;
			}
			case SC_LOGOUT_INFO:
			{
				SC_LOGOUT_INFO_PACKET* p = reinterpret_cast<SC_LOGOUT_INFO_PACKET*>(packet);
				std::lock_guard <std::mutex> l_g{ _lock };
				_state = p->s_state;
				for(PLAYER& pl : _players) {
					if (pl._id == p->id) {
						pl.erase();
						break;
					}
				}
				break;
			}
			case SC_MATCH_INFO:
			{
				std::cout << "SC_MATCH_INFO received" << std::endl;
				SC_MATCH_INFO_PACKET* p = reinterpret_cast<SC_MATCH_INFO_PACKET*>(packet);
				std::lock_guard <std::mutex> l_g{ _lock };
				_state = p->s_state;
				for (int i = 0; i < MAX_USER; i++) {
					strcpy(_players[i]._name, p->name[i]);
					_players[i].p_state = p->p_state[i];
					_players[i].x_pos = p->x[i];
					_players[i].y_pos = p->y[i];
					_players[i].hp = p->hp[i];
					//_players[i].ani_index = p->tick[i];
					break;
				}
				break;
			}
			case SC_MATCH_END:
			{
				break;
			}
			case SC_UPDATE:
			{
				/*std::cout << "SC_UPDATE received" << std::endl;
				SC_UPDATE_PACKET* p = reinterpret_cast<SC_UPDATE_PACKET*>(packet);
				std::lock_guard <std::mutex> l_g{ _lock };
				_state = p->s_state;
				for (PLAYER& pl : _players) {
					if (pl._id == p->id) {
						pl.p_state = p->p_state;
						pl.x_pos = p->x;
						pl.y_pos = p->y;
						pl.hp = p->hp;
						break;
					}
				}*/
				break;
			}
			default:
			{
				break;
			}
			}
		}
		else {
			std::cout << "Client disconnected. ID: " << _players[0]._id << std::endl;
			_players[0].connected = false;
			break;
		}
		print();
	}
}

void SESSION::update()
{

}
