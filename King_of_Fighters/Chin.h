#pragma once
#include "character.h"
#include "action.h"



class Chin : public Character {
public:
	Chin();
	~Chin() = default;
	HDC mirrorDC;
	HBITMAP mirrorBMP;
	HBITMAP mirrorOld;

	void init();
	void print(HDC& hdc);
	void reverse_print(HDC& hdc);
};