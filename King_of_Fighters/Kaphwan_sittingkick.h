#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_sittingkick {
public:
	IMAGE sittingkick_ani[4]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Kaphwan_sittingkick();
	~Kaphwan_sittingkick();

	void sittingkick_img_load();
	void goto_next_img();
};