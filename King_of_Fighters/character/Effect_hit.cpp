#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Effect_hit.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Hit::Hit() {};

Hit::~Hit() {};

void Hit::hit_img_load() {
	hit_ani[0].img.Load(L"HIT1.png");
	hit_ani[1].img.Load(L"HIT2.png");
	hit_ani[2].img.Load(L"HIT3.png");
	hit_ani[3].img.Load(L"HIT4.png");
	hit_ani[4].img.Load(L"HIT5.png");
	hit_ani[5].img.Load(L"HIT6.png");
	hit_ani[6].img.Load(L"HIT7.png");
	hit_ani[7].img.Load(L"HIT8.png");
	hit_ani[8].img.Load(L"HIT9.png");
	std::cout << "히트 이펙트 이미지 로드됨" << std::endl;
}

void Hit::goto_next_img()
{
	ani_index++;
}
