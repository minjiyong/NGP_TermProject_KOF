#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_bigpunch.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_bigpunch::Chin_bigpunch() {};

Chin_bigpunch::~Chin_bigpunch() {};

void Chin_bigpunch::bigpunch_img_load() {
	bigpunch_ani[0].img.Load(L"Chin Gentsai_77.png");
	bigpunch_ani[1].img.Load(L"Chin Gentsai_78.png");
	bigpunch_ani[2].img.Load(L"Chin Gentsai_79.png");
	bigpunch_ani[3].img.Load(L"Chin Gentsai_79.png");
	bigpunch_ani[4].img.Load(L"Chin Gentsai_78.png");
	bigpunch_ani[5].img.Load(L"Chin Gentsai_77.png");
	std::cout << "강손 이미지 로드됨" << std::endl;
}

void Chin_bigpunch::goto_next_img()
{
	ani_index++;
}
