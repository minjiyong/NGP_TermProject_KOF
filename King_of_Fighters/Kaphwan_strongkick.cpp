#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_strongkick.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_strongkick::Kaphwan_strongkick() {};

Kaphwan_strongkick::~Kaphwan_strongkick() {};

void Kaphwan_strongkick::strongkick_img_load() {
	strongkick_ani[0].img.Load(L"Kim Kaphwan_52.png");
	strongkick_ani[1].img.Load(L"Kim Kaphwan_53.png");
	strongkick_ani[2].img.Load(L"Kim Kaphwan_55.png");
	strongkick_ani[3].img.Load(L"Kim Kaphwan_56.png");
	strongkick_ani[4].img.Load(L"Kim Kaphwan_56.png");
	strongkick_ani[5].img.Load(L"Kim Kaphwan_55.png");
	strongkick_ani[6].img.Load(L"Kim Kaphwan_53.png");
	strongkick_ani[7].img.Load(L"Kim Kaphwan_52.png");
	std::cout << "강한 발 공격 이미지 로드됨" << std::endl;
}

void Kaphwan_strongkick::goto_next_img()
{
	ani_index++;
}
