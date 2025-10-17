#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_sittinghit.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_sittinghit::Kaphwan_sittinghit() {};

Kaphwan_sittinghit::~Kaphwan_sittinghit() {};

void Kaphwan_sittinghit::sittinghit_img_load() {
	sittinghit_ani[0].img.Load(L"Kim Kaphwan_131.png");
	sittinghit_ani[1].img.Load(L"Kim Kaphwan_132.png");
	sittinghit_ani[2].img.Load(L"Kim Kaphwan_133.png");
	sittinghit_ani[3].img.Load(L"Kim Kaphwan_132.png");
	std::cout << "¾É¾Æ ÇÇ°Ý ÀÌ¹ÌÁö ·ÎµåµÊ" << std::endl;
}

void Kaphwan_sittinghit::goto_next_img()
{
	ani_index++;
}
