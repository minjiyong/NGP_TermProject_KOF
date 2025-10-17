#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_jumpsmallpunch.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_jumpsmallpunch::Chin_jumpsmallpunch() {};

Chin_jumpsmallpunch::~Chin_jumpsmallpunch() {};

void Chin_jumpsmallpunch::jumpsmallpunch_img_load() {
	jumpsmallpunch_ani[0].img.Load(L"Chin Gentsai_58.png");
	jumpsmallpunch_ani[1].img.Load(L"Chin Gentsai_59.png");
	jumpsmallpunch_ani[2].img.Load(L"Chin Gentsai_60.png");
	jumpsmallpunch_ani[3].img.Load(L"Chin Gentsai_60.png");
	jumpsmallpunch_ani[4].img.Load(L"Chin Gentsai_59.png");
	jumpsmallpunch_ani[5].img.Load(L"Chin Gentsai_58.png");
	std::cout << "점프 약손 이미지 로드됨" << std::endl;
}

void Chin_jumpsmallpunch::goto_next_img()
{
	ani_index++;
}
