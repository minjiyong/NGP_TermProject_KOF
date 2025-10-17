#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_bigkick {
public:
	IMAGE bigkick_ani[8]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Chin_bigkick();
	~Chin_bigkick();

	void bigkick_img_load();
	void goto_next_img();
};