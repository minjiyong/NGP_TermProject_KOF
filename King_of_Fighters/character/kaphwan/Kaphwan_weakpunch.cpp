#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_weakpunch.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_weakpunch::Kaphwan_weakpunch() {};

Kaphwan_weakpunch::~Kaphwan_weakpunch() {};

void Kaphwan_weakpunch::weakpunch_img_load() {
	weakpunch_ani[0].img.Load(L"Kim Kaphwan_38.png");
	weakpunch_ani[1].img.Load(L"Kim Kaphwan_39.png");
	weakpunch_ani[2].img.Load(L"Kim Kaphwan_39.png");
	weakpunch_ani[3].img.Load(L"Kim Kaphwan_38.png");
	std::cout << "약한 손 공격 이미지 로드됨" << std::endl;
}

void Kaphwan_weakpunch::goto_next_img()
{
	ani_index++;
}
