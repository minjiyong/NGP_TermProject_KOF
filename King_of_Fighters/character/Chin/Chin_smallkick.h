#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_smallkick {
public:
	IMAGE smallkick_ani[5]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Chin_smallkick();
	~Chin_smallkick();

	void smallkick_img_load();
	void goto_next_img();
};