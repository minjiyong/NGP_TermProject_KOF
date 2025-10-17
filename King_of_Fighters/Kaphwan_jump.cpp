#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_jump.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_jump::Kaphwan_jump() {};

Kaphwan_jump::~Kaphwan_jump() {};

void Kaphwan_jump::jump_img_load() {
	jump_ani[0].img.Load(L"Kim Kaphwan_16.png");
	jump_ani[1].img.Load(L"Kim Kaphwan_17.png");
	jump_ani[2].img.Load(L"Kim Kaphwan_18.png");
	jump_ani[3].img.Load(L"Kim Kaphwan_19.png");
	jump_ani[4].img.Load(L"Kim Kaphwan_19.png");
	jump_ani[5].img.Load(L"Kim Kaphwan_19.png");
	jump_ani[6].img.Load(L"Kim Kaphwan_19.png");
	jump_ani[7].img.Load(L"Kim Kaphwan_19.png");
	jump_ani[8].img.Load(L"Kim Kaphwan_18.png");
	jump_ani[9].img.Load(L"Kim Kaphwan_17.png");
	jump_ani[10].img.Load(L"Kim Kaphwan_16.png");
	std::cout << "점프 이미지 로드됨" << std::endl;
}

void Kaphwan_jump::goto_next_img()
{
	ani_index++;
}
