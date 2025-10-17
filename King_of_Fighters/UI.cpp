#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "UI.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

#define HP 0
#define MAP1_1 1
#define MAP1_2 2
#define MAP1_3 3
#define CHINNAME 4
#define KAPNAME 5
#define KAPPROFILE 6
#define CHINPROFILE 7
#define TIME0 8
#define TIME1 9
#define TIME2 10
#define TIME3 11
#define TIME4 12
#define TIME5 13
#define TIME6 14
#define TIME7 15
#define TIME8 16
#define TIME9 17
#define START1 18
#define START2 19
#define FIGHT 20
#define KO 21

UI::UI() {};

UI::~UI() {};

void UI::UI_img_load() {
	UIindex[HP].img.Load(L"HPbar.png");
	UIindex[MAP1_1].img.Load(L"Background 1-1.png");
	UIindex[MAP1_2].img.Load(L"Background 1-2.png");
	UIindex[MAP1_3].img.Load(L"Background 1-3.png");
	UIindex[CHINNAME].img.Load(L"Chin_name.png");
	UIindex[KAPNAME].img.Load(L"Kap_name.png");
	UIindex[KAPPROFILE].img.Load(L"Kap_profile.png");
	UIindex[CHINPROFILE].img.Load(L"Chin_profile.png");
	UIindex[TIME0].img.Load(L"Time0.png");
	UIindex[TIME1].img.Load(L"Time1.png");
	UIindex[TIME2].img.Load(L"Time2.png");
	UIindex[TIME3].img.Load(L"Time3.png");
	UIindex[TIME4].img.Load(L"Time4.png");
	UIindex[TIME5].img.Load(L"Time5.png");
	UIindex[TIME6].img.Load(L"Time6.png");
	UIindex[TIME7].img.Load(L"Time7.png");
	UIindex[TIME8].img.Load(L"Time8.png");
	UIindex[TIME9].img.Load(L"Time9.png");
	UIindex[START1].img.Load(L"Start1.png");
	UIindex[START2].img.Load(L"Start2.png");
	UIindex[FIGHT].img.Load(L"Fight.png");
	UIindex[KO].img.Load(L"KO.png");
}