#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_frontmove.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_frontmove::Chin_frontmove() {};

Chin_frontmove::~Chin_frontmove() {};

void Chin_frontmove::frontmove_img_load() {
	frontmove_ani[0].img.Load(L"Chin Gentsai_9.png");
	frontmove_ani[1].img.Load(L"Chin Gentsai_10.png");
	frontmove_ani[2].img.Load(L"Chin Gentsai_11.png");
	frontmove_ani[3].img.Load(L"Chin Gentsai_12.png");
	frontmove_ani[4].img.Load(L"Chin Gentsai_13.png");
	frontmove_ani[5].img.Load(L"Chin Gentsai_14.png");
	frontmove_ani[6].img.Load(L"Chin Gentsai_15.png");
	std::cout << "전진 이미지 로드됨" << std::endl;
}

void Chin_frontmove::goto_next_img()
{
	ani_index++;
	if (ani_index == 7) ani_index = 0;
}
