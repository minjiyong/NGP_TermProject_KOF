#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_standinghit.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_standinghit::Kaphwan_standinghit() {};

Kaphwan_standinghit::~Kaphwan_standinghit() {};

void Kaphwan_standinghit::standinghit_img_load() {
	standinghit_ani[0].img.Load(L"Kim Kaphwan_125.png");
	standinghit_ani[1].img.Load(L"Kim Kaphwan_126.png");
	standinghit_ani[2].img.Load(L"Kim Kaphwan_127.png");
	standinghit_ani[3].img.Load(L"Kim Kaphwan_126.png");
	std::cout << "스탠딩 피격 이미지 로드됨" << std::endl;
}

void Kaphwan_standinghit::goto_next_img()
{
	ani_index++;
}
