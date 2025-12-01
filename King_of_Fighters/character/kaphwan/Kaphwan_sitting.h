#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_sitting {
public:
	IMAGE sitting_ani[1]{};
	int ani_index{ 0 };

	Kaphwan_sitting();
	~Kaphwan_sitting();

	void sitting_img_load();
	void goto_next_img();
};