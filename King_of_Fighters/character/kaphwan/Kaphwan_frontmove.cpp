#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_frontmove.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

Kaphwan_frontmove::Kaphwan_frontmove() {};

Kaphwan_frontmove::~Kaphwan_frontmove() {};

void Kaphwan_frontmove::frontmove_img_load() {
	frontmove_ani[0].img.Load(L"Kim Kaphwan_4.png");
	frontmove_ani[1].img.Load(L"Kim Kaphwan_5.png");
	frontmove_ani[2].img.Load(L"Kim Kaphwan_6.png");
	frontmove_ani[3].img.Load(L"Kim Kaphwan_7.png");
	frontmove_ani[4].img.Load(L"Kim Kaphwan_8.png");
	frontmove_ani[5].img.Load(L"Kim Kaphwan_9.png");
	std::cout << "전진 이미지 로드됨" << std::endl;
}

void Kaphwan_frontmove::goto_next_img()
{
	ani_index++;
	if (ani_index == 6) {
		ani_index = 0;
	}
}
