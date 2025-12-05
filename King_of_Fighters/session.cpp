#include "session.h"

void SESSION::print() const {
	std::cout << "------------------------" << std::endl;
	std::cout << "session ID: " << _id << std::endl;
	std::cout << "Session State: " << (int)_state << std::endl;
	for(const PLAYER& p : _players) {
		std::cout << "------------------------" << std::endl;
		std::cout << "Session ID: " << p._id << std::endl;
		std::cout << "Name: " << p._name << std::endl;
		std::cout << "m_state: " << (int)p.p_state << std::endl;
		std::cout << "Position: (" << p.x_pos << ", " << p.y_pos << ")" << std::endl;
		std::cout << "ani_index: " << p.ani_index << std::endl;
	}
	std::cout << "------------------------" << std::endl;
}

void SESSION::send_login_packet() const {
	CS_LOGIN_PACKET p;
	p.size = sizeof(CS_LOGIN_PACKET);
	p.type = CS_LOGIN;
	send_packet(_socket, &p);
}

void SESSION::send_name_info_packet(const char* s_name) const {
	CS_NAME_INFO_PACKET p;
	p.size = sizeof(CS_NAME_INFO_PACKET);
	p.type = CS_NAME_INFO;
	strcpy(p.name, s_name);
	std::cout << "Sending name: " << p.name << std::endl;
	send_packet(_socket, &p);
}

void SESSION::send_input_packet(Chin& chin) const{
	CS_INPUT_PACKET p;
	p.size = sizeof(CS_INPUT_PACKET);
	p.type = CS_INPUT;
	p.p_state = chin.p_state;
	send_packet(_socket, &p);
}

void SESSION::start_network(HWND& hWnd) {
	_recv_thread = std::thread(&SESSION::recv_thread, this, std::ref(hWnd));
	_recv_thread.detach();
	send_login_packet();
}

void SESSION::recv_thread(HWND& hWnd) {
	while (true) {
		if (_socket == 0) break;
		if (recv_packet(_socket, &_recv_buf)) {
			switch (_recv_buf[1]) {
			case SC_LOGIN_INFO:
			{
				SC_LOGIN_INFO_PACKET* p = reinterpret_cast<SC_LOGIN_INFO_PACKET*>(_recv_buf);
				std::lock_guard <std::mutex> l_g{ _lock };
				_id = p->id;
				_state = p->s_state;
				_connected = true;

				std::cout << "SC_LOGIN_INFO received. Assigned ID: " << _id << std::endl;
				break;
			}
			case SC_LOGOUT_INFO:
			{
				SC_LOGOUT_INFO_PACKET* p = reinterpret_cast<SC_LOGOUT_INFO_PACKET*>(_recv_buf);
				std::lock_guard <std::mutex> l_g{ _lock };
				_state = p->s_state;
				for(PLAYER& pl : _players) {
					if (pl._id == p->id) {
						pl.erase();
					}
				}
				break;
			}
			case SC_PLAYER_INFO:
			{
				std::cout << "SC_PLAYER_INFO received" << std::endl;
				SC_PLAYER_INFO_PACKET* p = reinterpret_cast<SC_PLAYER_INFO_PACKET*>(_recv_buf);
				std::lock_guard <std::mutex> l_g{ _lock };
				_state = p->s_state;
				for (int i = 0; i < MAX_USER; i++) {
					_players[i]._id = p->id[i];
					std::cout << p->id[i] << std::endl;
					strcpy(_players[i]._name, p->name[i]);
				}
				break;
			}
			case SC_MATCH_INFO:
			{
				std::cout << "SC_MATCH_INFO received" << std::endl;
				SC_MATCH_INFO_PACKET* p = reinterpret_cast<SC_MATCH_INFO_PACKET*>(_recv_buf);
				std::lock_guard <std::mutex> l_g{ _lock };
				_state = p->s_state;
				for (int i = 0; i < MAX_USER; i++) {
					_players[i]._id = p->id[i];
					strcpy(_players[i]._name, p->name[i]);
					_players[i].p_state = p->p_state[i];
					_players[i].x_pos = p->x[i];
					_players[i].y_pos = p->y[i];
					_players[i].hp = p->hp[i];
					_players[i].ani_index = p->tick[i];
				}
				break;
			}
			case SC_MATCH_END:
			{
				SC_MATCH_END_PACKET* p = reinterpret_cast<SC_MATCH_END_PACKET*>(_recv_buf);
				std::lock_guard <std::mutex> l_g{ _lock };
				_state = p->s_state;
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
		InvalidateRect(hWnd, nullptr, FALSE);
	}
}

void SESSION::update()
{

}
