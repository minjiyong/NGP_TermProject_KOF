#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_backmove {
public:
	IMAGE backmove_ani[6]{};
	int ani_index{ 0 };

	Kaphwan_backmove();
	~Kaphwan_backmove();

	void backmove_img_load();
	void goto_next_img();
};