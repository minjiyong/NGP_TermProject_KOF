#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"

class Kaphwan_sittingguard {
public:
	IMAGE sittingguard_ani[3]{};
	int ani_index{ 0 };

	Kaphwan_sittingguard();
	~Kaphwan_sittingguard();

	void sittingguard_img_load();
	void goto_next_img();
};