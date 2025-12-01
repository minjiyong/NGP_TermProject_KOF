#pragma once
#include "headers.h"

class PLAYER
{
public:
	int				_id;
	char			_name[NAME_SIZE];
	bool			connected;

	int				hp;
	int				x_pos;
	int				y_pos;

	P_STATE			p_state;
	int				ani_index{};
public:
	PLAYER() = default;
	~PLAYER() = default;

	void erase() {
		_id = 0;
		memset(_name, 0, NAME_SIZE);
		connected = false;
	}
};