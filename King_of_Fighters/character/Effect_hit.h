#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Hit {
public:
	IMAGE hit_ani[10]{};
	int ani_index{ 0 };

	Hit();
	~Hit();

	void hit_img_load();
	void goto_next_img();
};