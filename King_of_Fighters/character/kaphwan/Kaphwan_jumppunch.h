#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_jumppunch {
public:
	IMAGE jumppunch_ani[6]{};
	int ani_index{ 0 };

	RECT hitbox{};

	Kaphwan_jumppunch();
	~Kaphwan_jumppunch();

	void jumppunch_img_load();
	void goto_next_img();
};