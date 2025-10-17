#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_backmove {
public:
	IMAGE backmove_ani[5]{};
	int ani_index{ 0 };

	Chin_backmove();
	~Chin_backmove();

	void backmove_img_load();
	void goto_next_img();
};