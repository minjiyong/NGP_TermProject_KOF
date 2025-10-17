#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_downsmallkick.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_downsmallkick::Chin_downsmallkick() {};

Chin_downsmallkick::~Chin_downsmallkick() {};

void Chin_downsmallkick::downsmallkick_img_load() {
	downsmallkick_ani[0].img.Load(L"Chin Gentsai_65.png");
	downsmallkick_ani[1].img.Load(L"Chin Gentsai_66.png");
	downsmallkick_ani[2].img.Load(L"Chin Gentsai_67.png");
	downsmallkick_ani[3].img.Load(L"Chin Gentsai_67.png");
	downsmallkick_ani[4].img.Load(L"Chin Gentsai_66.png");
	downsmallkick_ani[5].img.Load(L"Chin Gentsai_65.png");
	std::cout << "하단약발 이미지 로드됨" << std::endl;
}

void Chin_downsmallkick::goto_next_img()
{
	ani_index++;
}
