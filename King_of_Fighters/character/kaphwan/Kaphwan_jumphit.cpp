#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_jumphit.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_jumphit::Kaphwan_jumphit() {};

Kaphwan_jumphit::~Kaphwan_jumphit() {};

void Kaphwan_jumphit::jumphit_img_load() {
	jumphit_ani[0].img.Load(L"Kim Kaphwan_128.png");
	jumphit_ani[1].img.Load(L"Kim Kaphwan_129.png");
	jumphit_ani[2].img.Load(L"Kim Kaphwan_130.png");
	jumphit_ani[3].img.Load(L"Kim Kaphwan_134.png");
	jumphit_ani[4].img.Load(L"Kim Kaphwan_135.png");
	jumphit_ani[5].img.Load(L"Kim Kaphwan_136.png");
	jumphit_ani[6].img.Load(L"Kim Kaphwan_137.png");
	std::cout << "점프 피격 이미지 로드됨" << std::endl;
}

void Kaphwan_jumphit::goto_next_img()
{
	ani_index++;
}
