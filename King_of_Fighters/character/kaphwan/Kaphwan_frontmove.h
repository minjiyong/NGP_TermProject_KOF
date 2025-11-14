#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_frontmove {
public:
	IMAGE frontmove_ani[6]{};
	int ani_index{ 0 };

	Kaphwan_frontmove();
	~Kaphwan_frontmove();

	void frontmove_img_load();
	void goto_next_img();
};