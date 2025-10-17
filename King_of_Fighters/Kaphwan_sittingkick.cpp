#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_sittingkick.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_sittingkick::Kaphwan_sittingkick() {};

Kaphwan_sittingkick::~Kaphwan_sittingkick() {};

void Kaphwan_sittingkick::sittingkick_img_load() {
	sittingkick_ani[0].img.Load(L"Kim Kaphwan_60.png");
	sittingkick_ani[1].img.Load(L"Kim Kaphwan_61.png");
	sittingkick_ani[2].img.Load(L"Kim Kaphwan_61.png");
	sittingkick_ani[3].img.Load(L"Kim Kaphwan_60.png");
	std::cout << "앉아 발차기 이미지 로드됨" << std::endl;
}

void Kaphwan_sittingkick::goto_next_img()
{
	ani_index++;
}
