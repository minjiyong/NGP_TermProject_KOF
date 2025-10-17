#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_sittinghit {
public:
	IMAGE sittinghit_ani[4]{};
	int ani_index{ 0 };

	Kaphwan_sittinghit();
	~Kaphwan_sittinghit();

	void sittinghit_img_load();
	void goto_next_img();
};