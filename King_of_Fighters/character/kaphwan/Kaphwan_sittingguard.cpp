#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Kaphwan_sittingguard.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan_sittingguard::Kaphwan_sittingguard() {};

Kaphwan_sittingguard::~Kaphwan_sittingguard() {};

void Kaphwan_sittingguard::sittingguard_img_load() {
	sittingguard_ani[0].img.Load(L"Kim Kaphwan_35.png");
	sittingguard_ani[1].img.Load(L"Kim Kaphwan_36.png");
	sittingguard_ani[2].img.Load(L"Kim Kaphwan_37.png");
	std::cout << "¾É¾Æ °¡µå ÀÌ¹ÌÁö ·ÎµåµÊ" << std::endl;
}

void Kaphwan_sittingguard::goto_next_img()
{
	ani_index++;
}
