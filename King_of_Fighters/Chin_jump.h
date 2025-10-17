#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_jump {
public:
	IMAGE jump_ani[11]{};
	int ani_index{ 0 };

	Chin_jump();
	~Chin_jump();

	void jump_img_load();
	void goto_next_img();
};