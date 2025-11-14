#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_smallpunch.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_smallpunch::Chin_smallpunch() {};

Chin_smallpunch::~Chin_smallpunch() {};

void Chin_smallpunch::smallpunch_img_load() {
	smallpunch_ani[0].img.Load(L"Chin Gentsai_52.png");
	smallpunch_ani[1].img.Load(L"Chin Gentsai_53.png");
	smallpunch_ani[2].img.Load(L"Chin Gentsai_53.png");
	smallpunch_ani[3].img.Load(L"Chin Gentsai_52.png");
	std::cout << "약손 이미지 로드됨" << std::endl;
}

void Chin_smallpunch::goto_next_img()
{
	ani_index++;
}
