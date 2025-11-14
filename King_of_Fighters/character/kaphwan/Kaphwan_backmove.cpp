#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_backmove.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

Kaphwan_backmove::Kaphwan_backmove() {};

Kaphwan_backmove::~Kaphwan_backmove() {};

void Kaphwan_backmove::backmove_img_load() {
	backmove_ani[0].img.Load(L"Kim Kaphwan_10.png");
	backmove_ani[1].img.Load(L"Kim Kaphwan_11.png");
	backmove_ani[2].img.Load(L"Kim Kaphwan_12.png");
	backmove_ani[3].img.Load(L"Kim Kaphwan_13.png");
	backmove_ani[4].img.Load(L"Kim Kaphwan_14.png");
	backmove_ani[5].img.Load(L"Kim Kaphwan_15.png");
	std::cout << "후진 이미지 로드됨" << std::endl;
}

void Kaphwan_backmove::goto_next_img()
{
	ani_index++;
	if (ani_index == 6) {
		ani_index = 0;
	}
}
