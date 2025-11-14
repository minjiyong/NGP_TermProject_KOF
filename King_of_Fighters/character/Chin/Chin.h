#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"
#include "Chin_standing.h"
#include "Chin_frontmove.h"
#include "Chin_backmove.h"
#include "Chin_jump.h"
#include "Chin_sitdown.h"
#include "Chin_smallpunch.h"
#include "Chin_downsmallpunch.h"
#include "Chin_jumpsmallpunch.h"
#include "Chin_bigpunch.h"
#include "Chin_smallkick.h"
#include "Chin_downsmallkick.h"
#include "Chin_jumpsmallkick.h"
#include "Chin_bigkick.h"
#include "Chin_standinghit.h"
#include "Chin_standingguard.h"
#include "Chin_sittinghit.h"
#include "Chin_sittingguard.h"
#include "Chin_jumphit.h"

class Chin
{
public:
	int img_left{};
	int img_top{};
	int img_right{};
	int img_bottom{};

	int condition1{};
	int condition2{1};
	int condition3{100};

	RECT hitbox{};

	Chin_standing standing_chin{};
	Chin_frontmove frontmove_chin{};
	Chin_backmove backmove_chin{};
	Chin_jump jump_chin{};
	Chin_sitdown sitdown_chin{};
	Chin_smallpunch smallpunch_chin{}; 
	Chin_downsmallpunch downsmallpunch_chin{}; 
	Chin_jumpsmallpunch jumpsmallpunch_chin{}; 
	Chin_bigpunch bigpunch_chin{};
	Chin_smallkick smallkick_chin{};
	Chin_downsmallkick downsmallkick_chin{};
	Chin_jumpsmallkick jumpsmallkick_chin{};
	Chin_bigkick bigkick_chin{};
	Chin_standinghit standinghit_chin{};
	Chin_standingguard standingguard_chin{};
	Chin_sittinghit sittinghit_chin{};
	Chin_sittingguard sittingguard_chin{};
	Chin_jumphit jumphit_chin{};

	Chin();
	~Chin();
	
	void initialize_chin();
	void print_standing_chin(HDC mDC);
	void print_frontmove_chin(HDC mDC);
	void print_backmove_chin(HDC mDC);
	void print_jump_chin(HDC mDC);
	void print_sitdown_chin(HDC mDC);
	void print_smallpunch_chin(HDC mDC);
	void print_downsmallpunch_chin(HDC mDC);
	void print_jumpsmallpunch_chin(HDC mDC);
	void print_bigpunch_chin(HDC mDC);
	void print_smallkick_chin(HDC mDC);
	void print_downsmallkick_chin(HDC mDC);
	void print_jumpsmallkick_chin(HDC mDC);
	void print_bigkick_chin(HDC mDC);
	void print_standinghit_chin(HDC mDC);
	void print_standingguard_chin(HDC mDC);
	void print_sittinghit_chin(HDC mDC);
	void print_sittingguard_chin(HDC mDC);
	void print_jumphit_chin(HDC mDC);
};