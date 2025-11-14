#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_frontmove {
public:
	IMAGE frontmove_ani[7]{};
	int ani_index{ 0 };

	Chin_frontmove();
	~Chin_frontmove();

	void frontmove_img_load();
	void goto_next_img();
};