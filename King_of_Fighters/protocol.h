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
constexpr char SC_PLAYER_INFO = 2;
constexpr char SC_MATCH_INFO = 3;
constexpr char SC_MATCH_END = 4;

// Client to Server Packet Types
constexpr char CS_LOGIN = 5;
constexpr char CS_NAME_INFO = 6;
constexpr char CS_INPUT = 7;

//--------------------------------------------------------------
// Movement and Action State Definitions
//--------------------------------------------------------------
enum P_STATE { // 플레이어 상태
	PS_Idle,
	PS_CrouchIdle,
	PS_JumpIdle,
	//----------------------------
	PS_BackMove,
	PS_ForwardMove,
	//----------------------------
	PS_standguard,
	PS_crouchguard,
	//----------------------------
	PS_standhit,
	PS_crouchhit,
	PS_jumphit,
	//----------------------------
	PS_punch_crouch,
	PS_punch_jump,
	PS_kick_crouch,
	PS_kick_jump,
	//----------------------------
	PS_punch_weak,
	PS_punch_strong,
	PS_kick_weak,
	PS_kick_strong,
	//----------------------------
};

//--------------------------------------------------------------
// Session State Definitions
//--------------------------------------------------------------
enum S_STATE { // 세션 상태
	ST_FREE,
	ST_CONNECT,
	ST_WAITGAME,
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
	S_STATE			s_state;
	int				id;
};

struct SC_LOGOUT_INFO_PACKET {
	unsigned char	size;
	char			type;
	S_STATE			s_state;
	int				id;
};

struct SC_PLAYER_INFO_PACKET {
	unsigned char	size;
	char			type;
	S_STATE			s_state;
	int				id[MAX_USER];
	char			name[MAX_USER][NAME_SIZE];
};

struct SC_MATCH_INFO_PACKET {
	unsigned char	size;
	char			type;
	S_STATE			s_state;
	int				id[MAX_USER];
	char			name[MAX_USER][NAME_SIZE];
	P_STATE			p_state[MAX_USER];
	int				x[MAX_USER];
	int				y[MAX_USER];
	int				hp[MAX_USER];
	int				tick[MAX_USER];
};

struct SC_MATCH_END_PACKET {
	unsigned char	size;
	char			type;
	S_STATE			s_state;
};

//--------------------------------------------------------------
// Client to Server Packets
//--------------------------------------------------------------
struct CS_LOGIN_PACKET {
	unsigned char	size;
	char			type;
};

struct CS_NAME_INFO_PACKET {
	unsigned char	size;
	char			type;
	char			name[NAME_SIZE];
};

struct CS_INPUT_PACKET {
	unsigned char	size;
	char			type;
	P_STATE			p_state;
};
#pragma pack (pop)