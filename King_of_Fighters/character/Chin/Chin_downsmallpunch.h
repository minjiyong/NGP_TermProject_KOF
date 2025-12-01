#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_downsmallpunch {
public:
	IMAGE downsmallpunch_ani[4]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Chin_downsmallpunch();
	~Chin_downsmallpunch();

	void downsmallpunch_img_load();
	void goto_next_img();
};