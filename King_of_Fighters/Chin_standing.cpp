#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_standing.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_standing::Chin_standing() {};

Chin_standing::~Chin_standing() {};

void Chin_standing::standing_img_load() {
	standing_ani[0].img.Load(L"Chin Gentsai_0.png");
	standing_ani[1].img.Load(L"Chin Gentsai_1.png");
	standing_ani[2].img.Load(L"Chin Gentsai_2.png");
	standing_ani[3].img.Load(L"Chin Gentsai_3.png");
	standing_ani[4].img.Load(L"Chin Gentsai_4.png");
	standing_ani[5].img.Load(L"Chin Gentsai_5.png");
	standing_ani[6].img.Load(L"Chin Gentsai_6.png");
	standing_ani[7].img.Load(L"Chin Gentsai_7.png");
	standing_ani[8].img.Load(L"Chin Gentsai_8.png");
	std::cout << "½ºÅÄµù ÀÌ¹ÌÁö ·ÎµåµÊ" << std::endl;
}

void Chin_standing::goto_next_img()
{
	ani_index++;
	if (ani_index == 9) ani_index = 0;
}
