#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_strongpunch {
public:
	IMAGE strongpunch_ani[6]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Kaphwan_strongpunch();
	~Kaphwan_strongpunch();

	void strongpunch_img_load();
	void goto_next_img();
};