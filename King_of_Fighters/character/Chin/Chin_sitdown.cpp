#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_sitdown.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_sitdown::Chin_sitdown() {};

Chin_sitdown::~Chin_sitdown() {};

void Chin_sitdown::sitdown_img_load() {
	sitdown_ani[0].img.Load(L"Chin Gentsai_33.png");
	std::cout << "¾É±â ÀÌ¹ÌÁö ·ÎµåµÊ" << std::endl;
}

void Chin_sitdown::goto_next_img()
{
	ani_index++;
	if (ani_index == 1) ani_index = 0;
}
