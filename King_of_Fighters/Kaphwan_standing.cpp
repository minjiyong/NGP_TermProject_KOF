#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_standing.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_standing::Kaphwan_standing() {};

Kaphwan_standing::~Kaphwan_standing() {};

void Kaphwan_standing::standing_img_load() {
	standing_ani[0].img.Load(L"Kim Kaphwan_0.png");
	standing_ani[1].img.Load(L"Kim Kaphwan_1.png");
	standing_ani[2].img.Load(L"Kim Kaphwan_2.png");
	standing_ani[3].img.Load(L"Kim Kaphwan_3.png");
	std::cout << "½ºÅÄµù ÀÌ¹ÌÁö ·ÎµåµÊ" << std::endl;
}

void Kaphwan_standing::goto_next_img()
{
	ani_index++;
	if (ani_index == 4) ani_index = 0;
}
