#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_jumphit.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_jumphit::Chin_jumphit() {};

Chin_jumphit::~Chin_jumphit() {};

void Chin_jumphit::jumphit_img_load() {
	jumphit_ani[0].img.Load(L"Chin Gentsai_185.png");
	jumphit_ani[1].img.Load(L"Chin Gentsai_188.png");
	jumphit_ani[2].img.Load(L"Chin Gentsai_189.png");
	jumphit_ani[3].img.Load(L"Chin Gentsai_190.png");
	jumphit_ani[4].img.Load(L"Chin Gentsai_191.png");
	jumphit_ani[5].img.Load(L"Chin Gentsai_192.png");
	jumphit_ani[6].img.Load(L"Chin Gentsai_192.png");
}

void Chin_jumphit::goto_next_img()
{
	ani_index++;
}
