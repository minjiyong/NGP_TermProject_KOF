#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_jumpkick {
public:
	IMAGE jumpkick_ani[6]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Kaphwan_jumpkick();
	~Kaphwan_jumpkick();

	void jumpkick_img_load();
	void goto_next_img();
};