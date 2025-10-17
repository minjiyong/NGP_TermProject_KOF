#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_weakpunch {
public:
	IMAGE weakpunch_ani[4]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Kaphwan_weakpunch();
	~Kaphwan_weakpunch();

	void weakpunch_img_load();
	void goto_next_img();
};