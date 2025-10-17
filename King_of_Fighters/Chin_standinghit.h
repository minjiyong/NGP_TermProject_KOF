#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_standinghit {
public:
	IMAGE standinghit_ani[4]{};
	int ani_index{ 0 };

	Chin_standinghit();
	~Chin_standinghit();

	void standinghit_img_load();
	void goto_next_img();
};