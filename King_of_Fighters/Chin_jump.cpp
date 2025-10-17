#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_jump.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_jump::Chin_jump() {};

Chin_jump::~Chin_jump() {};

void Chin_jump::jump_img_load() {
	jump_ani[0].img.Load(L"Chin Gentsai_21.png");
	jump_ani[1].img.Load(L"Chin Gentsai_22.png");
	jump_ani[2].img.Load(L"Chin Gentsai_23.png");
	jump_ani[3].img.Load(L"Chin Gentsai_24.png");
	jump_ani[4].img.Load(L"Chin Gentsai_24.png");
	jump_ani[5].img.Load(L"Chin Gentsai_24.png");
	jump_ani[6].img.Load(L"Chin Gentsai_24.png");
	jump_ani[7].img.Load(L"Chin Gentsai_24.png");
	jump_ani[8].img.Load(L"Chin Gentsai_23.png");
	jump_ani[9].img.Load(L"Chin Gentsai_22.png");
	jump_ani[10].img.Load(L"Chin Gentsai_21.png");
	std::cout << "점프 이미지 로드됨" << std::endl;
}

void Chin_jump::goto_next_img()
{
	ani_index++;
}
