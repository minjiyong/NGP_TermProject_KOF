#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"
#include "Kaphwan_standing.h"

#include "Kaphwan_frontmove.h"
#include "Kaphwan_backmove.h"
#include "Kaphwan_jump.h"
#include "Kaphwan_sitting.h"

#include "Kaphwan_standingguard.h"
#include "Kaphwan_sittingguard.h"

#include "Kaphwan_weakpunch.h"
#include "Kaphwan_strongpunch.h"
#include "Kaphwan_weakkick.h"
#include "Kaphwan_strongkick.h"

#include "Kaphwan_standinghit.h"
#include "Kaphwan_sittinghit.h"
#include "Kaphwan_jumphit.h"

#include "Kaphwan_sittingpunch.h"
#include "Kaphwan_sittingkick.h"

#include "Kaphwan_jumppunch.h"
#include "Kaphwan_jumpkick.h"

class Kaphwan
{
public:
	int img_left{};
	int img_top{};
	int img_right{};
	int img_bottom{};

	int condition1{};
	int condition2{ 1 };
	int condition3{ 100 };

	RECT hitbox{};

	Kaphwan_standing standing_kaphwan{};
	Kaphwan_frontmove frontmove_kaphwan{};
	Kaphwan_backmove backmove_kaphwan{};
	Kaphwan_jump jump_kaphwan{};
	Kaphwan_sitting sitting_kaphwan{};

	Kaphwan_standingguard standingguard_kaphwan{};
	Kaphwan_sittingguard sittingguard_kaphwan{};

	Kaphwan_weakpunch weakpunch_kaphwan{};
	Kaphwan_strongpunch strongpunch_kaphwan{};
	Kaphwan_weakkick weakkick_kaphwan{};
	Kaphwan_strongkick strongkick_kaphwan{};

	Kaphwan_standinghit standinghit_kaphwan{};
	Kaphwan_sittinghit sittinghit_kaphwan{};
	Kaphwan_jumphit jumphit_kaphwan{};

	Kaphwan_sittingpunch sittingpunch_kaphwan{};
	Kaphwan_sittingkick sittingkick_kaphwan{};

	Kaphwan_jumppunch jumppunch_kaphwan{};
	Kaphwan_jumpkick jumpkick_kaphwan{};


	Kaphwan();
	~Kaphwan();
	

	void initialize_kaphwan();

	void print_standing_kaphwan(HDC mDC);
	void print_frontmove_kaphwan(HDC mDC);
	void print_backmove_kaphwan(HDC mDC);
	void print_jump_kaphwan(HDC mDC);
	void print_sitting_kaphwan(HDC mDC);

	void print_standingguard_kaphwan(HDC mDC);
	void print_sittingguard_kaphwan(HDC mDC);

	void print_weakpunch_kaphwan(HDC mDC);
	void print_strongpunch_kaphwan(HDC mDC);
	void print_weakkick_kaphwan(HDC mDC);
	void print_strongkick_kaphwan(HDC mDC);

	void print_standinghit_kaphwan(HDC mDC);
	void print_sittinghit_kaphwan(HDC mDC);
	void print_jumphit_kaphwan(HDC mDC);

	void print_sittingpunch_kaphwan(HDC mDC);
	void print_sittingkick_kaphwan(HDC mDC);

	void print_jumppunch_kaphwan(HDC mDC);
	void print_jumpkick_kaphwan(HDC mDC);
};