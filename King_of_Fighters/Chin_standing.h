#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_standing {
public:
	IMAGE standing_ani[9]{};
	int ani_index{ 0 };

	Chin_standing();
	~Chin_standing();

	void standing_img_load();
	void goto_next_img();
};