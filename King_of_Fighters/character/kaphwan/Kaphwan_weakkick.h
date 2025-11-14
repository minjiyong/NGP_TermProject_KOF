#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_weakkick {
public:
	IMAGE weakkick_ani[6]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Kaphwan_weakkick();
	~Kaphwan_weakkick();

	void weakkick_img_load();
	void goto_next_img();
};