#pragma once
#include "headers.h"

class PLAYER
{
public:
	int				_id;
	char			_name[NAME_SIZE];
	bool			connected;

	float			hp;
	int				x_pos;
	int				y_pos;

	P_MOVE_STATE	m_state;
	P_ATTACK_STATE	a_state;
	P_GUARD_STATE	g_state;
	P_HIT_STATE		h_state;

public:
	PLAYER() = default;
	~PLAYER() = default;

	void erase() {
		_id = 0;
		memset(_name, 0, NAME_SIZE);
		connected = false;
	}
};