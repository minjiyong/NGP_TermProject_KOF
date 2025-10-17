#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class UI {
public:
	IMAGE UIindex[22]{};
	int img_left[22]{};
	int img_top[22]{};
	int img_right[22]{};
	int img_bottom[22]{};

	UI();
	~UI();

	void UI_img_load();
};