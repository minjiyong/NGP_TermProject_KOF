#include "NetworkModule.h"

void InitialzeNetwork(SESSION& session)
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;

	// 소켓 생성
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

	// 이름을 입력 받고 그 이름을 서버로 전송
	CS_LOGIN_PACKET p;
	sprintf_s(p.name, "%d", "player");
	p.size = sizeof(CS_LOGIN_PACKET);
	p.type = CS_LOGIN;

	send_packet(session._socket, &p);
}