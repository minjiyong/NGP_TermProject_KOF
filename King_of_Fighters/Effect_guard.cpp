#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Effect_guard.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Guard::Guard() {};

Guard::~Guard() {};

void Guard::guard_img_load() {
	guard_ani[0].img.Load(L"GUARD1.png");
	guard_ani[1].img.Load(L"GUARD2.png");
	guard_ani[2].img.Load(L"GUARD3.png");
	guard_ani[3].img.Load(L"GUARD4.png");
	guard_ani[4].img.Load(L"GUARD5.png");
	guard_ani[5].img.Load(L"GUARD6.png");
	guard_ani[6].img.Load(L"GUARD7.png");
	guard_ani[7].img.Load(L"GUARD8.png");
	guard_ani[8].img.Load(L"GUARD9.png");
	std::cout << "가드 이펙트 이미지 로드됨" << std::endl;
}

void Guard::goto_next_img()
{
	ani_index++;
}
