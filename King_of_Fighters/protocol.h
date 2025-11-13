#pragma once
// Protocol definitions for server-client communication in a multiplayer game.
//--------------------------------------------------------------
constexpr short GAME_PORT = 9000;
constexpr int MAX_USER = 3;
constexpr int BUF_SIZE = 200;
constexpr unsigned short MAP_HEIGHT = 0;
constexpr unsigned short MAP_WIDTH = 0;
constexpr int NAME_SIZE = 20;

//--------------------------------------------------------------
// Packet Type Definitions
//--------------------------------------------------------------
// Server to Client Packet Types
constexpr char SC_LOGIN_INFO = 0;
constexpr char SC_LOGOUT_INFO = 1;
constexpr char SC_UPDATE = 2;

// Client to Server Packet Types
constexpr char CS_LOGIN = 3;
constexpr char CS_INPUT = 4;

//--------------------------------------------------------------
// Movement and Action State Definitions
//--------------------------------------------------------------
enum P_MOVE_STATE {
	PMS_NONE,
	PMS_LEFT,
	PMS_RIGHT,
	PMS_SIT,
	PMS_SIT_LEFT,
	PMS_SIT_RIGHT,
	PMS_JUMP,
	PMS_JUMP_LEFT,
	PMS_JUMP_RIGHT
};

enum P_ATTACK_STATE {
	PAS_NONE,
	PAS_LIGHT_HAND,
	PAS_LIGHT_FOOT,
	PAS_HEAVY_HAND,
	PAS_HEAVY_FOOT
};

enum P_GUARD_STATE {
	PGS_NONE,
	PGS_STAND,
	PGS_SIT
};

enum P_HIT_STATE {
	PHS_NONE,
	PHS_STAND,
	PHS_SIT
};

//--------------------------------------------------------------
// Session State Definitions
//--------------------------------------------------------------
enum S_STATE { // 세션 상태
	ST_FREE,
	ST_CONNECT,
	ST_INGAME,
	ST_OUTGAME,
	ST_DISCONNECT
};

#pragma pack (push, 1)
//--------------------------------------------------------------
// Server to Client Packets
//--------------------------------------------------------------
struct SC_LOGIN_INFO_PACKET {
	unsigned char	size;
	char			type;
	int				id;
};

struct SC_LOGOUT_INFO_PACKET {
	unsigned char	size;
	char			type;
	int				id;
};

struct SC_UPDATE_PACKET {
	unsigned char	size;
	char			type;
	int				id;
	P_MOVE_STATE	m_state;
	P_ATTACK_STATE	a_state;
	P_GUARD_STATE	g_state;
	P_HIT_STATE		h_state;
	int				x;
	int				y;
	int				hp;
};

//--------------------------------------------------------------
// Client to Server Packets
//--------------------------------------------------------------
struct CS_LOGIN_PACKET {
	unsigned char	size;
	char			type;
	char			name[NAME_SIZE];
};

struct CS_INPUT_PACKET {
	unsigned char	size;
	char			type;
	P_MOVE_STATE	m_state;
	P_ATTACK_STATE	a_state;
	P_GUARD_STATE	g_state;
	P_HIT_STATE		h_state;
};
#pragma pack (pop)