#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_strongkick {
public:
	IMAGE strongkick_ani[8]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Kaphwan_strongkick();
	~Kaphwan_strongkick();

	void strongkick_img_load();
	void goto_next_img();
};