#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_smallkick.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_smallkick::Chin_smallkick() {};

Chin_smallkick::~Chin_smallkick() {};

void Chin_smallkick::smallkick_img_load() {
	smallkick_ani[0].img.Load(L"Chin Gentsai_63.png");
	smallkick_ani[1].img.Load(L"Chin Gentsai_64.png");
	smallkick_ani[2].img.Load(L"Chin Gentsai_64.png");
	smallkick_ani[3].img.Load(L"Chin Gentsai_63.png");
	smallkick_ani[4].img.Load(L"Chin Gentsai_63.png");
	std::cout << "약발 이미지 로드됨" << std::endl;
}

void Chin_smallkick ::goto_next_img()
{
	ani_index++;
}
