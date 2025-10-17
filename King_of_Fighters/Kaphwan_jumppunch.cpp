#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_jumppunch.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_jumppunch::Kaphwan_jumppunch() {};

Kaphwan_jumppunch::~Kaphwan_jumppunch() {};

void Kaphwan_jumppunch::jumppunch_img_load() {
	jumppunch_ani[0].img.Load(L"Kim Kaphwan_44.png");
	jumppunch_ani[1].img.Load(L"Kim Kaphwan_44.png");
	jumppunch_ani[2].img.Load(L"Kim Kaphwan_45.png");
	jumppunch_ani[3].img.Load(L"Kim Kaphwan_45.png");
	jumppunch_ani[4].img.Load(L"Kim Kaphwan_44.png");
	jumppunch_ani[5].img.Load(L"Kim Kaphwan_44.png");
	std::cout << "Á¡ÇÁ ÁÖ¸Ô ÀÌ¹ÌÁö ·ÎµåµÊ" << std::endl;
}

void Kaphwan_jumppunch::goto_next_img()
{
	ani_index++;
}
