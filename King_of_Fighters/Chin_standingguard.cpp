#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_standingguard.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_standingguard::Chin_standingguard() {};

Chin_standingguard::~Chin_standingguard() {};

void Chin_standingguard::standingguard_img_load() {
	standingguard_ani[0].img.Load(L"Chin Gentsai_144.png");
	standingguard_ani[1].img.Load(L"Chin Gentsai_144.png");
	standingguard_ani[2].img.Load(L"Chin Gentsai_144.png");
	std::cout << "스탠딩 가드 이미지 로드됨" << std::endl;
}

void Chin_standingguard::goto_next_img()
{
	ani_index++;
}
