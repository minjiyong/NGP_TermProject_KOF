#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_downsmallpunch.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_downsmallpunch::Chin_downsmallpunch() {};

Chin_downsmallpunch::~Chin_downsmallpunch() {};

void Chin_downsmallpunch::downsmallpunch_img_load() {
	downsmallpunch_ani[0].img.Load(L"Chin Gentsai_54.png");
	downsmallpunch_ani[1].img.Load(L"Chin Gentsai_55.png");
	downsmallpunch_ani[2].img.Load(L"Chin Gentsai_55.png");
	downsmallpunch_ani[3].img.Load(L"Chin Gentsai_54.png");
	std::cout << "하단 약손 이미지 로드됨" << std::endl;
}

void Chin_downsmallpunch::goto_next_img()
{
	ani_index++;
}
