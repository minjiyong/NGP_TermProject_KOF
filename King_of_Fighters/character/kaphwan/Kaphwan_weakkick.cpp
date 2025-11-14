#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_weakkick.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_weakkick::Kaphwan_weakkick() {};

Kaphwan_weakkick::~Kaphwan_weakkick() {};

void Kaphwan_weakkick::weakkick_img_load() {
	weakkick_ani[0].img.Load(L"Kim Kaphwan_48.png");
	weakkick_ani[1].img.Load(L"Kim Kaphwan_49.png");
	weakkick_ani[2].img.Load(L"Kim Kaphwan_50.png");
	weakkick_ani[3].img.Load(L"Kim Kaphwan_50.png");
	weakkick_ani[4].img.Load(L"Kim Kaphwan_49.png");
	weakkick_ani[5].img.Load(L"Kim Kaphwan_48.png");
	std::cout << "약한 발 공격 이미지 로드됨" << std::endl;
}

void Kaphwan_weakkick::goto_next_img()
{
	ani_index++;
}
