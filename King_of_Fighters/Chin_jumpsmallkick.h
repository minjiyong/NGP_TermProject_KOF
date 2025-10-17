#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_jumpsmallkick {
public:
	IMAGE jumpsmallkick_ani[6]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Chin_jumpsmallkick();
	~Chin_jumpsmallkick();

	void jumpsmallkick_img_load();
	void goto_next_img();
};