#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_jumphit {
public:
	IMAGE jumphit_ani[7]{};
	int ani_index{ 0 };

	Chin_jumphit();
	~Chin_jumphit();

	void jumphit_img_load();
	void goto_next_img();
};