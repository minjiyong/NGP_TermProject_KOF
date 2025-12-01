#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_jumpsmallpunch {
public:
	IMAGE jumpsmallpunch_ani[6]{};
	int ani_index{ 0 };

	RECT hitbox{};
	
	Chin_jumpsmallpunch();
	~Chin_jumpsmallpunch();

	void jumpsmallpunch_img_load();
	void goto_next_img();
};