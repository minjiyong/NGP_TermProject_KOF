#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_sitdown {
public:
	IMAGE sitdown_ani[1]{};
	int ani_index{ 0 };

	Chin_sitdown();
	~Chin_sitdown();

	void sitdown_img_load();
	void goto_next_img();
};