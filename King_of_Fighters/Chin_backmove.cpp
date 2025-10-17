#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_backmove.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_backmove::Chin_backmove() {};

Chin_backmove::~Chin_backmove() {};

void Chin_backmove::backmove_img_load() {
	backmove_ani[0].img.Load(L"Chin Gentsai_16.png");
	backmove_ani[1].img.Load(L"Chin Gentsai_17.png");
	backmove_ani[2].img.Load(L"Chin Gentsai_18.png");
	backmove_ani[3].img.Load(L"Chin Gentsai_19.png");
	backmove_ani[4].img.Load(L"Chin Gentsai_20.png");
	std::cout << "후진 이미지 로드됨" << std::endl;
}

void Chin_backmove::goto_next_img()
{
	ani_index++;
	if (ani_index == 5) ani_index = 0;
}
