#pragma once
#include <windows.h>
#include <iostream>
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
#include "Chin.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin::Chin() {}

Chin::~Chin() {}

void Chin::initialize_chin()
{
	standing_chin.standing_img_load();
	for (int i = 0; i < 9; ++i) {
		standing_chin.standing_ani[i].ImageInitialize();
	}
	frontmove_chin.frontmove_img_load();
	for (int i = 0; i < 7; ++i) {
		frontmove_chin.frontmove_ani[i].ImageInitialize();
	}
	backmove_chin.backmove_img_load();
	for (int i = 0; i < 5; ++i) {
		backmove_chin.backmove_ani[i].ImageInitialize();
	}
	jump_chin.jump_img_load();
	for (int i = 0; i < 11; ++i) {
		jump_chin.jump_ani[i].ImageInitialize();
	}
	sitdown_chin.sitdown_img_load();
	for (int i = 0; i < 1; ++i) {
		sitdown_chin.sitdown_ani[i].ImageInitialize();
	}
	smallpunch_chin.smallpunch_img_load();
	for (int i = 0; i < 4; ++i) {
		smallpunch_chin.smallpunch_ani[i].ImageInitialize();
	}
	downsmallpunch_chin.downsmallpunch_img_load();
	for (int i = 0; i < 4; ++i) {
		downsmallpunch_chin.downsmallpunch_ani[i].ImageInitialize();
	}
	jumpsmallpunch_chin.jumpsmallpunch_img_load();
	for (int i = 0; i < 6; ++i) {
		jumpsmallpunch_chin.jumpsmallpunch_ani[i].ImageInitialize();
	}
	bigpunch_chin.bigpunch_img_load();
	for (int i = 0; i < 6; ++i) {
		bigpunch_chin.bigpunch_ani[i].ImageInitialize();
	}
	smallkick_chin.smallkick_img_load();
	for (int i = 0; i < 5; ++i) {
		smallkick_chin.smallkick_ani[i].ImageInitialize();
	}
	downsmallkick_chin.downsmallkick_img_load();
	for (int i = 0; i < 6; ++i) {
		downsmallkick_chin.downsmallkick_ani[i].ImageInitialize();
	}
	jumpsmallkick_chin.jumpsmallkick_img_load();
	for (int i = 0; i < 6; ++i) {
		jumpsmallkick_chin.jumpsmallkick_ani[i].ImageInitialize();
	}
	bigkick_chin.bigkick_img_load();
	for (int i = 0; i < 8; ++i) {
		bigkick_chin.bigkick_ani[i].ImageInitialize();
	}
	standinghit_chin.standinghit_img_load();
	for (int i = 0; i < 4; ++i) {
		standinghit_chin.standinghit_ani[i].ImageInitialize();
	}
	standingguard_chin.standingguard_img_load();
	for (int i = 0; i < 3; ++i) {
		standingguard_chin.standingguard_ani[i].ImageInitialize();
	}
	sittinghit_chin.sittinghit_img_load();
	for (int i = 0; i < 4; ++i) {
		sittinghit_chin.sittinghit_ani[i].ImageInitialize();
	}
	sittingguard_chin.sittingguard_img_load();
	for (int i = 0; i < 3; ++i) {
		sittingguard_chin.sittingguard_ani[i].ImageInitialize();
	}
	jumphit_chin.jumphit_img_load();
	for (int i = 0; i < 7; ++i) {
		jumphit_chin.jumphit_ani[i].ImageInitialize();
	}
}

void Chin::print_standing_chin(HDC mDC)
{
	img_right = img_left + standing_chin.standing_ani[standing_chin.ani_index].img_width;
	img_bottom = img_top + standing_chin.standing_ani[standing_chin.ani_index].img_height;

	hitbox.left = img_left + 12;
	hitbox.top = img_top;
	hitbox.right = img_left + 91;
	hitbox.bottom = img_top + 191;

	standing_chin.standing_ani[standing_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, standing_chin.standing_ani[standing_chin.ani_index].img_width, standing_chin.standing_ani[standing_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_frontmove_chin(HDC mDC)
{
	img_right = img_left + frontmove_chin.frontmove_ani[frontmove_chin.ani_index].img_width;
	img_bottom = img_top + frontmove_chin.frontmove_ani[frontmove_chin.ani_index].img_height;
	frontmove_chin.frontmove_ani[frontmove_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, frontmove_chin.frontmove_ani[frontmove_chin.ani_index].img_width, frontmove_chin.frontmove_ani[frontmove_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_backmove_chin(HDC mDC)
{
	img_right = img_left + backmove_chin.backmove_ani[backmove_chin.ani_index].img_width;
	img_bottom = img_top + backmove_chin.backmove_ani[backmove_chin.ani_index].img_height;
	backmove_chin.backmove_ani[backmove_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, backmove_chin.backmove_ani[backmove_chin.ani_index].img_width, backmove_chin.backmove_ani[backmove_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_jump_chin(HDC mDC)
{
	img_right = img_left + jump_chin.jump_ani[jump_chin.ani_index].img_width;
	img_bottom = img_top + jump_chin.jump_ani[jump_chin.ani_index].img_height;
	jump_chin.jump_ani[jump_chin.ani_index].img.TransparentBlt(mDC, img_left - 20, img_top, img_right - img_left, img_bottom - img_top, 0, 0, jump_chin.jump_ani[jump_chin.ani_index].img_width, jump_chin.jump_ani[jump_chin.ani_index].img_height, RGB(8, 0, 99));

}


void Chin::print_sitdown_chin(HDC mDC)
{
	img_right = img_left + sitdown_chin.sitdown_ani[sitdown_chin.ani_index].img_width;
	img_bottom = img_top + sitdown_chin.sitdown_ani[sitdown_chin.ani_index].img_height;

	hitbox.top = img_top + 60;
	hitbox.bottom = img_top + 191;

	sitdown_chin.sitdown_ani[sitdown_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, sitdown_chin.sitdown_ani[sitdown_chin.ani_index].img_width, sitdown_chin.sitdown_ani[sitdown_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_smallpunch_chin(HDC mDC)
{
	img_right = img_left + smallpunch_chin.smallpunch_ani[smallpunch_chin.ani_index].img_width;
	img_bottom = img_top + smallpunch_chin.smallpunch_ani[smallpunch_chin.ani_index].img_height;

	if (smallpunch_chin.ani_index == 1 || smallpunch_chin.ani_index == 2) {
		smallpunch_chin.hitbox.left = img_right - 7;
		smallpunch_chin.hitbox.top = img_top + 60;
		smallpunch_chin.hitbox.right = img_right + 19;
		smallpunch_chin.hitbox.bottom = img_top + 82;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		smallpunch_chin.hitbox.left = -1000;
		smallpunch_chin.hitbox.top = -1000;
		smallpunch_chin.hitbox.right = -1000;
		smallpunch_chin.hitbox.bottom = -1000;
	}

	smallpunch_chin.smallpunch_ani[smallpunch_chin.ani_index].img.TransparentBlt(mDC, img_left + 20, img_top, img_right - img_left, img_bottom - img_top, 0, 0, smallpunch_chin.smallpunch_ani[smallpunch_chin.ani_index].img_width, smallpunch_chin.smallpunch_ani[smallpunch_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_downsmallpunch_chin(HDC mDC)
{
	img_right = img_left + downsmallpunch_chin.downsmallpunch_ani[downsmallpunch_chin.ani_index].img_width;
	img_bottom = img_top + downsmallpunch_chin.downsmallpunch_ani[downsmallpunch_chin.ani_index].img_height;

	if (downsmallpunch_chin.ani_index == 1 || downsmallpunch_chin.ani_index == 2) {
		downsmallpunch_chin.hitbox.left = img_right - 20;
		downsmallpunch_chin.hitbox.top = img_top + 101;
		downsmallpunch_chin.hitbox.right = img_right;
		downsmallpunch_chin.hitbox.bottom = img_top + 122;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}	
	else {
		downsmallpunch_chin.hitbox.left = -1000;
		downsmallpunch_chin.hitbox.top = -1000;
		downsmallpunch_chin.hitbox.right = -1000;
		downsmallpunch_chin.hitbox.bottom = -1000;
	}

	downsmallpunch_chin.downsmallpunch_ani[downsmallpunch_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, downsmallpunch_chin.downsmallpunch_ani[downsmallpunch_chin.ani_index].img_width, downsmallpunch_chin.downsmallpunch_ani[downsmallpunch_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_jumpsmallpunch_chin(HDC mDC)
{
	img_right = img_left + jumpsmallpunch_chin.jumpsmallpunch_ani[jumpsmallpunch_chin.ani_index].img_width;
	img_bottom = img_top + jumpsmallpunch_chin.jumpsmallpunch_ani[jumpsmallpunch_chin.ani_index].img_height;

	if (jumpsmallpunch_chin.ani_index == 2 || jumpsmallpunch_chin.ani_index == 3) {
		jumpsmallpunch_chin.hitbox.left = img_right - 15;
		jumpsmallpunch_chin.hitbox.top = img_top + 135;
		jumpsmallpunch_chin.hitbox.right = img_right + 5;
		jumpsmallpunch_chin.hitbox.bottom = img_top + 157;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		jumpsmallpunch_chin.hitbox.left = -1000;
		jumpsmallpunch_chin.hitbox.top = -1000;
		jumpsmallpunch_chin.hitbox.right = -1000;
		jumpsmallpunch_chin.hitbox.bottom = -1000;
	}

	jumpsmallpunch_chin.jumpsmallpunch_ani[jumpsmallpunch_chin.ani_index].img.TransparentBlt(mDC, img_left + 10, img_top, img_right - img_left, img_bottom - img_top, 0, 0, jumpsmallpunch_chin.jumpsmallpunch_ani[jumpsmallpunch_chin.ani_index].img_width, jumpsmallpunch_chin.jumpsmallpunch_ani[jumpsmallpunch_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_bigpunch_chin(HDC mDC)
{
	img_right = img_left + bigpunch_chin.bigpunch_ani[bigpunch_chin.ani_index].img_width;
	img_bottom = img_top + bigpunch_chin.bigpunch_ani[bigpunch_chin.ani_index].img_height;

	if (bigpunch_chin.ani_index == 2 || bigpunch_chin.ani_index == 3) {
		bigpunch_chin.hitbox.left = img_right - 15;
		bigpunch_chin.hitbox.top = img_top + 54;
		bigpunch_chin.hitbox.right = img_right + 10;
		bigpunch_chin.hitbox.bottom = img_top + 74;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		bigpunch_chin.hitbox.left = -1000;
		bigpunch_chin.hitbox.top = -1000;
		bigpunch_chin.hitbox.right = -1000;
		bigpunch_chin.hitbox.bottom = -1000;
	}

	bigpunch_chin.bigpunch_ani[bigpunch_chin.ani_index].img.TransparentBlt(mDC, img_left + 10, img_top, img_right - img_left, img_bottom - img_top, 0, 0, bigpunch_chin.bigpunch_ani[bigpunch_chin.ani_index].img_width, bigpunch_chin.bigpunch_ani[bigpunch_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_smallkick_chin(HDC mDC)
{
	img_right = img_left + smallkick_chin.smallkick_ani[smallkick_chin.ani_index].img_width;
	img_bottom = img_top + smallkick_chin.smallkick_ani[smallkick_chin.ani_index].img_height;

	if (smallkick_chin.ani_index == 1 || smallkick_chin.ani_index == 2) {
		smallkick_chin.hitbox.left = img_right - 60;
		smallkick_chin.hitbox.top = img_top + 83;
		smallkick_chin.hitbox.right = img_right - 27;
		smallkick_chin.hitbox.bottom = img_top + 107;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		smallkick_chin.hitbox.left = -1000;
		smallkick_chin.hitbox.top = -1000;
		smallkick_chin.hitbox.right = -1000;
		smallkick_chin.hitbox.bottom = -1000;
	}

	smallkick_chin.smallkick_ani[smallkick_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, smallkick_chin.smallkick_ani[smallkick_chin.ani_index].img_width, smallkick_chin.smallkick_ani[smallkick_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_downsmallkick_chin(HDC mDC)
{
	img_right = img_left + downsmallkick_chin.downsmallkick_ani[downsmallkick_chin.ani_index].img_width;
	img_bottom = img_top + downsmallkick_chin.downsmallkick_ani[downsmallkick_chin.ani_index].img_height;

	if (downsmallkick_chin.ani_index == 2 || downsmallkick_chin.ani_index == 3) {
		downsmallkick_chin.hitbox.left = img_right - 60;
		downsmallkick_chin.hitbox.top = img_top + 173;
		downsmallkick_chin.hitbox.right = img_right - 27;
		downsmallkick_chin.hitbox.bottom = img_top + 191;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		downsmallkick_chin.hitbox.left = -1000;
		downsmallkick_chin.hitbox.top = -1000;
		downsmallkick_chin.hitbox.right = -1000;
		downsmallkick_chin.hitbox.bottom = -1000;
	}

	downsmallkick_chin.downsmallkick_ani[downsmallkick_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, downsmallkick_chin.downsmallkick_ani[downsmallkick_chin.ani_index].img_width, downsmallkick_chin.downsmallkick_ani[downsmallkick_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_jumpsmallkick_chin(HDC mDC)
{
	img_right = img_left + jumpsmallkick_chin.jumpsmallkick_ani[jumpsmallkick_chin.ani_index].img_width;
	img_bottom = img_top + jumpsmallkick_chin.jumpsmallkick_ani[jumpsmallkick_chin.ani_index].img_height;

	if (jumpsmallkick_chin.ani_index == 2 || jumpsmallkick_chin.ani_index == 3) {
		jumpsmallkick_chin.hitbox.left = img_right - 70;
		jumpsmallkick_chin.hitbox.top = img_top + 53;
		jumpsmallkick_chin.hitbox.right = img_right - 42;
		jumpsmallkick_chin.hitbox.bottom = img_top + 90;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		jumpsmallkick_chin.hitbox.left = -1000;
		jumpsmallkick_chin.hitbox.top = -1000;
		jumpsmallkick_chin.hitbox.right = -1000;
		jumpsmallkick_chin.hitbox.bottom = -1000;
	}

	jumpsmallkick_chin.jumpsmallkick_ani[jumpsmallkick_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, jumpsmallkick_chin.jumpsmallkick_ani[jumpsmallkick_chin.ani_index].img_width, jumpsmallkick_chin.jumpsmallkick_ani[jumpsmallkick_chin.ani_index].img_height, RGB(8, 0, 99));
	
}


void Chin::print_bigkick_chin(HDC mDC)
{
	img_right = img_left + bigkick_chin.bigkick_ani[bigkick_chin.ani_index].img_width;
	img_bottom = img_top + bigkick_chin.bigkick_ani[bigkick_chin.ani_index].img_height;

	if (bigkick_chin.ani_index == 4 || bigkick_chin.ani_index == 5) {
		bigkick_chin.hitbox.left = img_right - 70;
		bigkick_chin.hitbox.top = img_top + 109;
		bigkick_chin.hitbox.right = img_right - 39;
		bigkick_chin.hitbox.bottom = img_top + 131;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		bigkick_chin.hitbox.left = -1000;
		bigkick_chin.hitbox.top = -1000;
		bigkick_chin.hitbox.right = -1000;
		bigkick_chin.hitbox.bottom = -1000;
	}

	bigkick_chin.bigkick_ani[bigkick_chin.ani_index].img.TransparentBlt(mDC, img_left - 40, img_top, img_right - img_left, img_bottom - img_top, 0, 0, bigkick_chin.bigkick_ani[bigkick_chin.ani_index].img_width, bigkick_chin.bigkick_ani[bigkick_chin.ani_index].img_height, RGB(8, 0, 99));

}

void Chin::print_standinghit_chin(HDC mDC)
{
	img_right = img_left + standinghit_chin.standinghit_ani[standinghit_chin.ani_index].img_width;
	img_bottom = img_top + standinghit_chin.standinghit_ani[standinghit_chin.ani_index].img_height;
	standinghit_chin.standinghit_ani[standinghit_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, standinghit_chin.standinghit_ani[standinghit_chin.ani_index].img_width, standinghit_chin.standinghit_ani[standinghit_chin.ani_index].img_height, RGB(8, 0, 99));

}

void Chin::print_standingguard_chin(HDC mDC)
{
	img_right = img_left + standingguard_chin.standingguard_ani[standingguard_chin.ani_index].img_width;
	img_bottom = img_top + standingguard_chin.standingguard_ani[standingguard_chin.ani_index].img_height;
	standingguard_chin.standingguard_ani[standingguard_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, standingguard_chin.standingguard_ani[standingguard_chin.ani_index].img_width, standingguard_chin.standingguard_ani[standingguard_chin.ani_index].img_height, RGB(8, 0, 99));

}


void Chin::print_sittinghit_chin(HDC mDC)
{
	img_right = img_left + sittinghit_chin.sittinghit_ani[sittinghit_chin.ani_index].img_width;
	img_bottom = img_top + sittinghit_chin.sittinghit_ani[sittinghit_chin.ani_index].img_height;
	sittinghit_chin.sittinghit_ani[sittinghit_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, sittinghit_chin.sittinghit_ani[sittinghit_chin.ani_index].img_width, sittinghit_chin.sittinghit_ani[sittinghit_chin.ani_index].img_height, RGB(8, 0, 99));
}


void Chin::print_sittingguard_chin(HDC mDC)
{
	img_right = img_left + sittingguard_chin.sittingguard_ani[sittingguard_chin.ani_index].img_width;
	img_bottom = img_top + sittingguard_chin.sittingguard_ani[sittingguard_chin.ani_index].img_height;
	sittingguard_chin.sittingguard_ani[sittingguard_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, sittingguard_chin.sittingguard_ani[sittingguard_chin.ani_index].img_width, sittingguard_chin.sittingguard_ani[sittingguard_chin.ani_index].img_height, RGB(8, 0, 99));
}


void Chin::print_jumphit_chin(HDC mDC)
{
	img_right = img_left + jumphit_chin.jumphit_ani[jumphit_chin.ani_index].img_width;
	img_bottom = img_top + jumphit_chin.jumphit_ani[jumphit_chin.ani_index].img_height;
	jumphit_chin.jumphit_ani[jumphit_chin.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, jumphit_chin.jumphit_ani[jumphit_chin.ani_index].img_width, jumphit_chin.jumphit_ani[jumphit_chin.ani_index].img_height, RGB(8, 0, 99));
}