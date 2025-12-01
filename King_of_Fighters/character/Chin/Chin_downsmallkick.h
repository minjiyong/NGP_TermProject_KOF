#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_downsmallkick {
public:
	IMAGE downsmallkick_ani[6]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Chin_downsmallkick();
	~Chin_downsmallkick();

	void downsmallkick_img_load();
	void goto_next_img();
};