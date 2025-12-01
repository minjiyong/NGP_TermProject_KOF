#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_sitting.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_sitting::Kaphwan_sitting() {};

Kaphwan_sitting::~Kaphwan_sitting() {};

void Kaphwan_sitting::sitting_img_load() {
	sitting_ani[0].img.Load(L"Kim Kaphwan_29.png");
	std::cout << "¾É¾ÆÀÖ´Â ÀÌ¹ÌÁö ·ÎµåµÊ" << std::endl;
}

void Kaphwan_sitting::goto_next_img()
{
	ani_index++;
	if (ani_index == 1) {
		ani_index = 0;
	}
}
