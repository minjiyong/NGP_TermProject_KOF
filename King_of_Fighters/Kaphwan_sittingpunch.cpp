#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_sittingpunch.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_sittingpunch::Kaphwan_sittingpunch() {};

Kaphwan_sittingpunch::~Kaphwan_sittingpunch() {};

void Kaphwan_sittingpunch::sittingpunch_img_load() {
	sittingpunch_ani[0].img.Load(L"Kim Kaphwan_46.png");
	sittingpunch_ani[1].img.Load(L"Kim Kaphwan_47.png");
	sittingpunch_ani[2].img.Load(L"Kim Kaphwan_47.png");
	sittingpunch_ani[3].img.Load(L"Kim Kaphwan_46.png");
	std::cout << "¾É¾Æ ÁÖ¸Ô ÀÌ¹ÌÁö ·ÎµåµÊ" << std::endl;
}

void Kaphwan_sittingpunch::goto_next_img()
{
	ani_index++;
}
