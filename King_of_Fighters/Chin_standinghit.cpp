#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_standinghit.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_standinghit::Chin_standinghit() {};

Chin_standinghit::~Chin_standinghit() {};

void Chin_standinghit::standinghit_img_load() {
	standinghit_ani[0].img.Load(L"Chin Gentsai_75.png");
	standinghit_ani[1].img.Load(L"Chin Gentsai_75.png");
	standinghit_ani[2].img.Load(L"Chin Gentsai_75.png");
	standinghit_ani[3].img.Load(L"Chin Gentsai_75.png");
	std::cout << "스탠딩 피격 이미지 로드됨" << std::endl;
}

void Chin_standinghit::goto_next_img()
{
	ani_index++;
}
