#pragma once
#include "Chin.h"

class SESSION {
public:
	std::array<Chin, MAX_USER> _players;
	int			_id;
	bool		_connected;
	char		_recv_buf[BUF_SIZE];
	std::thread _recv_thread;	// receive thread
	std::mutex _lock;
	SOCKET		_socket;
	S_STATE		_state;
public:
	SESSION() = default;
	~SESSION() = default;

	void print();
	void start_network();
	void recv_thread();
	void update();
	void send_login_packet();
	void send_name_info_packet(const char* s_name);
	void send_input_packet(Chin& chin);
};