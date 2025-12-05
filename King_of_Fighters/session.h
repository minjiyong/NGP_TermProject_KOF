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

	void print() const;
	void start_network(HWND& hWnd);
	void recv_thread(HWND& hWnd);
	void update();
	void send_login_packet() const;
	void send_name_info_packet(const char* s_name) const;
	void send_input_packet(Chin& chin) const;
};