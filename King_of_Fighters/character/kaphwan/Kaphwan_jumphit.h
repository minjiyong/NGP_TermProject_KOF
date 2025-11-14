#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_jumphit {
public:
	IMAGE jumphit_ani[7]{};
	int ani_index{ 0 };

	Kaphwan_jumphit();
	~Kaphwan_jumphit();

	void jumphit_img_load();
	void goto_next_img();
}; 
