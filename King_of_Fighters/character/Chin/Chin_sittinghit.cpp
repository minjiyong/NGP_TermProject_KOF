#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_sittinghit.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_sittinghit::Chin_sittinghit() {};

Chin_sittinghit::~Chin_sittinghit() {};

void Chin_sittinghit::sittinghit_img_load() {
	sittinghit_ani[0].img.Load(L"Chin Gentsai_182.png");
	sittinghit_ani[1].img.Load(L"Chin Gentsai_183.png");
	sittinghit_ani[2].img.Load(L"Chin Gentsai_184.png");
	sittinghit_ani[3].img.Load(L"Chin Gentsai_184.png");
}

void Chin_sittinghit::goto_next_img()
{
	ani_index++;
}
