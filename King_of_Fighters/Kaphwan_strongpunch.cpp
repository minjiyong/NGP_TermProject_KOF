#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_strongpunch.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_strongpunch::Kaphwan_strongpunch() {};

Kaphwan_strongpunch::~Kaphwan_strongpunch() {};

void Kaphwan_strongpunch::strongpunch_img_load() {
	strongpunch_ani[0].img.Load(L"Kim Kaphwan_40.png");
	strongpunch_ani[1].img.Load(L"Kim Kaphwan_41.png");
	strongpunch_ani[2].img.Load(L"Kim Kaphwan_42.png");
	strongpunch_ani[3].img.Load(L"Kim Kaphwan_42.png");
	strongpunch_ani[4].img.Load(L"Kim Kaphwan_41.png");
	strongpunch_ani[5].img.Load(L"Kim Kaphwan_40.png");
	std::cout << "강한 손 공격 이미지 로드됨" << std::endl;
}

void Kaphwan_strongpunch::goto_next_img()
{
	ani_index++;
}
