#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Guard {
public:
	IMAGE guard_ani[10]{};
	int ani_index{ 0 };

	Guard();
	~Guard();

	void guard_img_load();
	void goto_next_img();
};