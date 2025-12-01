#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_bigpunch {
public:
	IMAGE bigpunch_ani[6]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Chin_bigpunch();
	~Chin_bigpunch();

	void bigpunch_img_load();
	void goto_next_img();
};