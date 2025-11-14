#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_standingguard.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_standingguard::Kaphwan_standingguard() {};

Kaphwan_standingguard::~Kaphwan_standingguard() {};

void Kaphwan_standingguard::standingguard_img_load() {
	standingguard_ani[0].img.Load(L"Kim Kaphwan_32.png");
	standingguard_ani[1].img.Load(L"Kim Kaphwan_33.png");
	standingguard_ani[2].img.Load(L"Kim Kaphwan_34.png");
	std::cout << "기본 가드 이미지 로드됨" << std::endl;
}

void Kaphwan_standingguard::goto_next_img()
{
	ani_index++;
}
