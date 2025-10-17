#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_jumpsmallkick.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_jumpsmallkick::Chin_jumpsmallkick() {};

Chin_jumpsmallkick::~Chin_jumpsmallkick() {};

void Chin_jumpsmallkick::jumpsmallkick_img_load() {
	jumpsmallkick_ani[0].img.Load(L"Chin Gentsai_68.png");
	jumpsmallkick_ani[1].img.Load(L"Chin Gentsai_69.png");
	jumpsmallkick_ani[2].img.Load(L"Chin Gentsai_70.png");
	jumpsmallkick_ani[3].img.Load(L"Chin Gentsai_70.png");
	jumpsmallkick_ani[4].img.Load(L"Chin Gentsai_69.png");
	jumpsmallkick_ani[5].img.Load(L"Chin Gentsai_68.png");
	std::cout << "점프 약발 이미지 로드됨" << std::endl;
}

void Chin_jumpsmallkick::goto_next_img()
{
	ani_index++;
}
