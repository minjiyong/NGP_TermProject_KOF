#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_jumpkick.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_jumpkick::Kaphwan_jumpkick() {};

Kaphwan_jumpkick::~Kaphwan_jumpkick() {};

void Kaphwan_jumpkick::jumpkick_img_load() {
	jumpkick_ani[0].img.Load(L"Kim Kaphwan_86.png");
	jumpkick_ani[1].img.Load(L"Kim Kaphwan_87.png");
	jumpkick_ani[2].img.Load(L"Kim Kaphwan_88.png");
	jumpkick_ani[3].img.Load(L"Kim Kaphwan_88.png");
	jumpkick_ani[4].img.Load(L"Kim Kaphwan_87.png");
	jumpkick_ani[5].img.Load(L"Kim Kaphwan_86.png");
	std::cout << "점프 발차기 이미지 로드됨" << std::endl;
}

void Kaphwan_jumpkick::goto_next_img()
{
	ani_index++;
}
