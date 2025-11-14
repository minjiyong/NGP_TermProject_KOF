#pragma once
#include "sound.h"
#include "ui.h"
#include "draw.h"
class GAMEMANAGER {
public:
	SOUND startMusic;
	UI ui;
	int mapTimer{};
	int timeone = 9;
	int timeten = 5;
	int start = 1;
	int fight = 0;
	bool ko = FALSE;
public:
	GAMEMANAGER();
	~GAMEMANAGER() = default;
	
	void printMap(HDC& mDC);
	void printHp(HDC& mDC, int p1_hp, int p2_hp, int p3_hp);
	void printName(HDC& mDC);
	void printProfile(HDC& mDC);
	void printTime(HDC& mDC);
	void printStart(HDC& mDC);
	void printFight(HDC& mDC);
	void printKO(HDC& mDC);
	void playbackgroundmusic();
};