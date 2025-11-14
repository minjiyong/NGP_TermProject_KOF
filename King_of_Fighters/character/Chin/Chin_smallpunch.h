#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_smallpunch {
public:
	IMAGE smallpunch_ani[4]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Chin_smallpunch();
	~Chin_smallpunch();

	void smallpunch_img_load();
	void goto_next_img();
};