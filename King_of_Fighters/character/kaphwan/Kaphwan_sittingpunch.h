#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_sittingpunch {
public:
	IMAGE sittingpunch_ani[4]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Kaphwan_sittingpunch();
	~Kaphwan_sittingpunch();

	void sittingpunch_img_load();
	void goto_next_img();
};