#pragma once
#include "headers.h"
#include "player.h"

class SESSION {
public:
	std::array<PLAYER, MAX_USER> _players;
	char		_recv_buf[BUF_SIZE];
	std::mutex _lock;
	SOCKET		_socket;
	S_STATE		_state;
public:
	void print();
	void recv_thread();
	void send_input_packet();
};