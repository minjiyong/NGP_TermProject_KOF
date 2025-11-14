#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_sittingguard.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_sittingguard::Chin_sittingguard() {};

Chin_sittingguard::~Chin_sittingguard() {};

void Chin_sittingguard::sittingguard_img_load() {
	sittingguard_ani[0].img.Load(L"Chin Gentsai_117.png");
	sittingguard_ani[1].img.Load(L"Chin Gentsai_117.png");
	sittingguard_ani[2].img.Load(L"Chin Gentsai_117.png");
}

void Chin_sittingguard::goto_next_img()
{
	ani_index++;
}
