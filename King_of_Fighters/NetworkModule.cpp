#include "NetworkModule.h"

void InitialzeNetwork(SESSION& session)
{
	int retval;

	// 扩加 檬扁拳
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;

	// 家南 积己
	session._socket = socket(AF_INET, SOCK_STREAM, 0);
	if (session._socket == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);
	serveraddr.sin_port = htons(GAME_PORT);
	retval = connect(session._socket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	session.send_login_packet();

	session.start_network();
}