#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"
#include "Effect_hit.h"
#include "Effect_guard.h"

class Effect
{
public:
	int img_left{};
	int img_top{};
	int img_right{};
	int img_bottom{};

	int condition{ 100 };

	Hit hit{};
	Guard guard{};

	Effect();
	~Effect();

	void Initialize_effect();
	void print_hit(HDC mDC);
	void print_guard(HDC mDC);
};