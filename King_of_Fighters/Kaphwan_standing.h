#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_standing {
public:
	IMAGE standing_ani[4]{};
	int ani_index{ 0 };

	Kaphwan_standing();
	~Kaphwan_standing();

	void standing_img_load();
	void goto_next_img();
};