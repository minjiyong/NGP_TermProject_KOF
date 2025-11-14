#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Chin_standingguard {
public:
	IMAGE standingguard_ani[3]{};
	int ani_index{ 0 };

	Chin_standingguard();
	~Chin_standingguard();

	void standingguard_img_load();
	void goto_next_img();
};