#pragma once
#include <windows.h>
#include <iostream>
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
#include "Kaphwan.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Kaphwan::Kaphwan(){}

Kaphwan::~Kaphwan(){}

void Kaphwan::initialize_kaphwan()
{
	standing_kaphwan.standing_img_load();
	for (int i = 0; i < 4; ++i) {
		standing_kaphwan.standing_ani[i].ImageInitialize();
	}
	frontmove_kaphwan.frontmove_img_load();
	for (int i = 0; i < 6; ++i) {
		frontmove_kaphwan.frontmove_ani[i].ImageInitialize();
	}
	backmove_kaphwan.backmove_img_load();
	for (int i = 0; i < 6; ++i) {
		backmove_kaphwan.backmove_ani[i].ImageInitialize();
	}
	jump_kaphwan.jump_img_load();
	for (int i = 0; i < 11; ++i) {
		jump_kaphwan.jump_ani[i].ImageInitialize();
	}
	sitting_kaphwan.sitting_img_load();
	sitting_kaphwan.sitting_ani[0].ImageInitialize();

	standingguard_kaphwan.standingguard_img_load();
	for (int i = 0; i < 3; ++i) {
		standingguard_kaphwan.standingguard_ani[i].ImageInitialize();
	}
	sittingguard_kaphwan.sittingguard_img_load();
	for (int i = 0; i < 3; ++i) {
		sittingguard_kaphwan.sittingguard_ani[i].ImageInitialize();
	}

	weakpunch_kaphwan.weakpunch_img_load();
	for (int i = 0; i < 4; ++i) {
		weakpunch_kaphwan.weakpunch_ani[i].ImageInitialize();
	}
	strongpunch_kaphwan.strongpunch_img_load();
	for (int i = 0; i < 6; ++i) {
		strongpunch_kaphwan.strongpunch_ani[i].ImageInitialize();
	}
	weakkick_kaphwan.weakkick_img_load();
	for (int i = 0; i < 6; ++i) {
		weakkick_kaphwan.weakkick_ani[i].ImageInitialize();
	}
	strongkick_kaphwan.strongkick_img_load();
	for (int i = 0; i < 8; ++i) {
		strongkick_kaphwan.strongkick_ani[i].ImageInitialize();
	}

	standinghit_kaphwan.standinghit_img_load();
	for (int i = 0; i < 4; ++i) {
		standinghit_kaphwan.standinghit_ani[i].ImageInitialize();
	}
	sittinghit_kaphwan.sittinghit_img_load();
	for (int i = 0; i < 4; ++i) {
		sittinghit_kaphwan.sittinghit_ani[i].ImageInitialize();
	}
	jumphit_kaphwan.jumphit_img_load();
	for (int i = 0; i < 7; ++i) {
		jumphit_kaphwan.jumphit_ani[i].ImageInitialize();
	}

	sittingpunch_kaphwan.sittingpunch_img_load();
	for (int i = 0; i < 4; ++i) {
		sittingpunch_kaphwan.sittingpunch_ani[i].ImageInitialize();
	}
	sittingkick_kaphwan.sittingkick_img_load();
	for (int i = 0; i < 4; ++i) {
		sittingkick_kaphwan.sittingkick_ani[i].ImageInitialize();
	}

	jumppunch_kaphwan.jumppunch_img_load();
	for (int i = 0; i < 6; ++i) {
		jumppunch_kaphwan.jumppunch_ani[i].ImageInitialize();
	}
	jumpkick_kaphwan.jumpkick_img_load();
	for (int i = 0; i < 6; ++i) {
		jumpkick_kaphwan.jumpkick_ani[i].ImageInitialize();
	}
}


void Kaphwan::print_standing_kaphwan(HDC mDC)
{
	img_right = img_left + standing_kaphwan.standing_ani[standing_kaphwan.ani_index].img_width;
	img_bottom = img_top + standing_kaphwan.standing_ani[standing_kaphwan.ani_index].img_height;

	hitbox.left = img_left + 30;
	hitbox.top = img_top + 30;
	hitbox.right = img_left + 110;
	hitbox.bottom = img_top + 224;

	standing_kaphwan.standing_ani[standing_kaphwan.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, standing_kaphwan.standing_ani[standing_kaphwan.ani_index].img_width, standing_kaphwan.standing_ani[standing_kaphwan.ani_index].img_height, RGB(8, 49, 132));

}

void Kaphwan::print_frontmove_kaphwan(HDC mDC)
{
	img_right = img_left + frontmove_kaphwan.frontmove_ani[frontmove_kaphwan.ani_index].img_width;
	img_bottom = img_top + frontmove_kaphwan.frontmove_ani[frontmove_kaphwan.ani_index].img_height;
	frontmove_kaphwan.frontmove_ani[frontmove_kaphwan.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, frontmove_kaphwan.frontmove_ani[frontmove_kaphwan.ani_index].img_width, frontmove_kaphwan.frontmove_ani[frontmove_kaphwan.ani_index].img_height, RGB(8, 49, 132));
	
}

void Kaphwan::print_backmove_kaphwan(HDC mDC)
{
	img_right = img_left + backmove_kaphwan.backmove_ani[backmove_kaphwan.ani_index].img_width;
	img_bottom = img_top + backmove_kaphwan.backmove_ani[backmove_kaphwan.ani_index].img_height;
	backmove_kaphwan.backmove_ani[backmove_kaphwan.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, backmove_kaphwan.backmove_ani[backmove_kaphwan.ani_index].img_width, backmove_kaphwan.backmove_ani[backmove_kaphwan.ani_index].img_height, RGB(8, 49, 132));
	
}

void Kaphwan::print_jump_kaphwan(HDC mDC)
{
	img_right = img_left + jump_kaphwan.jump_ani[jump_kaphwan.ani_index].img_width;
	img_bottom = img_top + jump_kaphwan.jump_ani[jump_kaphwan.ani_index].img_height;
	jump_kaphwan.jump_ani[jump_kaphwan.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, jump_kaphwan.jump_ani[jump_kaphwan.ani_index].img_width, jump_kaphwan.jump_ani[jump_kaphwan.ani_index].img_height, RGB(8, 49, 132));
	
}

void Kaphwan::print_sitting_kaphwan(HDC mDC)
{
	img_right = img_left + sitting_kaphwan.sitting_ani[sitting_kaphwan.ani_index].img_width;
	img_bottom = img_top + sitting_kaphwan.sitting_ani[sitting_kaphwan.ani_index].img_height;

	hitbox.left = img_left + 30;
	hitbox.top = img_top + 100;
	hitbox.right = img_left + 110;
	hitbox.bottom = img_top + 224;

	sitting_kaphwan.sitting_ani[sitting_kaphwan.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, sitting_kaphwan.sitting_ani[sitting_kaphwan.ani_index].img_width, sitting_kaphwan.sitting_ani[sitting_kaphwan.ani_index].img_height, RGB(8, 49, 132));
	
}

void Kaphwan::print_standingguard_kaphwan(HDC mDC)
{
	img_right = img_left + standingguard_kaphwan.standingguard_ani[standingguard_kaphwan.ani_index].img_width;
	img_bottom = img_top + standingguard_kaphwan.standingguard_ani[standingguard_kaphwan.ani_index].img_height;
	standingguard_kaphwan.standingguard_ani[standingguard_kaphwan.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, standingguard_kaphwan.standingguard_ani[standingguard_kaphwan.ani_index].img_width, standingguard_kaphwan.standingguard_ani[standingguard_kaphwan.ani_index].img_height, RGB(8, 49, 132));
	
}

void Kaphwan::print_sittingguard_kaphwan(HDC mDC)
{
	img_right = img_left + sittingguard_kaphwan.sittingguard_ani[sittingguard_kaphwan.ani_index].img_width;
	img_bottom = img_top + sittingguard_kaphwan.sittingguard_ani[sittingguard_kaphwan.ani_index].img_height;
	sittingguard_kaphwan.sittingguard_ani[sittingguard_kaphwan.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, sittingguard_kaphwan.sittingguard_ani[sittingguard_kaphwan.ani_index].img_width, sittingguard_kaphwan.sittingguard_ani[sittingguard_kaphwan.ani_index].img_height, RGB(8, 49, 132));
	
}

void Kaphwan::print_weakpunch_kaphwan(HDC mDC)
{
	img_right = img_left + weakpunch_kaphwan.weakpunch_ani[weakpunch_kaphwan.ani_index].img_width;
	img_bottom = img_top + weakpunch_kaphwan.weakpunch_ani[weakpunch_kaphwan.ani_index].img_height;

	if (weakpunch_kaphwan.ani_index == 1 || weakpunch_kaphwan.ani_index == 2) {
		weakpunch_kaphwan.hitbox.left = img_left - 30;
		weakpunch_kaphwan.hitbox.top = img_top + 55;
		weakpunch_kaphwan.hitbox.right = img_left + 2;
		weakpunch_kaphwan.hitbox.bottom = img_top + 78;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		weakpunch_kaphwan.hitbox.left = -1000;
		weakpunch_kaphwan.hitbox.top = -1000;
		weakpunch_kaphwan.hitbox.right = -1000;
		weakpunch_kaphwan.hitbox.bottom = -1000;
	}

	weakpunch_kaphwan.weakpunch_ani[weakpunch_kaphwan.ani_index].img.TransparentBlt(mDC, img_left - 32, img_top, img_right - img_left, img_bottom - img_top, 0, 0, weakpunch_kaphwan.weakpunch_ani[weakpunch_kaphwan.ani_index].img_width, weakpunch_kaphwan.weakpunch_ani[weakpunch_kaphwan.ani_index].img_height, RGB(8, 49, 132));
	
}

void Kaphwan::print_strongpunch_kaphwan(HDC mDC)
{
	img_right = img_left + strongpunch_kaphwan.strongpunch_ani[strongpunch_kaphwan.ani_index].img_width;
	img_bottom = img_top + strongpunch_kaphwan.strongpunch_ani[strongpunch_kaphwan.ani_index].img_height;

	if (strongpunch_kaphwan.ani_index == 2 || strongpunch_kaphwan.ani_index == 3) {
		strongpunch_kaphwan.hitbox.left = img_left - 70;
		strongpunch_kaphwan.hitbox.top = img_top + 89;
		strongpunch_kaphwan.hitbox.right = img_left - 47;
		strongpunch_kaphwan.hitbox.bottom = img_top + 108;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		strongpunch_kaphwan.hitbox.left = -1000;
		strongpunch_kaphwan.hitbox.top = -1000;
		strongpunch_kaphwan.hitbox.right = -1000;
		strongpunch_kaphwan.hitbox.bottom = -1000;
	}

	strongpunch_kaphwan.strongpunch_ani[strongpunch_kaphwan.ani_index].img.TransparentBlt(mDC, img_left - 100, img_top, img_right - img_left, img_bottom - img_top, 0, 0, strongpunch_kaphwan.strongpunch_ani[strongpunch_kaphwan.ani_index].img_width, strongpunch_kaphwan.strongpunch_ani[strongpunch_kaphwan.ani_index].img_height, RGB(8, 49, 132));

}

void Kaphwan::print_weakkick_kaphwan(HDC mDC)
{
	img_right = img_left + weakkick_kaphwan.weakkick_ani[weakkick_kaphwan.ani_index].img_width;
	img_bottom = img_top + weakkick_kaphwan.weakkick_ani[weakkick_kaphwan.ani_index].img_height;

	if (weakkick_kaphwan.ani_index == 2 || weakkick_kaphwan.ani_index == 3) {
		weakkick_kaphwan.hitbox.left = img_left - 40;
		weakkick_kaphwan.hitbox.top = img_top + 71;
		weakkick_kaphwan.hitbox.right = img_left - 8;
		weakkick_kaphwan.hitbox.bottom = img_top + 100;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		weakkick_kaphwan.hitbox.left = -1000;
		weakkick_kaphwan.hitbox.top = -1000;
		weakkick_kaphwan.hitbox.right = -1000;
		weakkick_kaphwan.hitbox.bottom = -1000;
	}

	weakkick_kaphwan.weakkick_ani[weakkick_kaphwan.ani_index].img.TransparentBlt(mDC, img_left - 48, img_top, img_right - img_left, img_bottom - img_top, 0, 0, weakkick_kaphwan.weakkick_ani[weakkick_kaphwan.ani_index].img_width, weakkick_kaphwan.weakkick_ani[weakkick_kaphwan.ani_index].img_height, RGB(8, 49, 132));
	
}

void Kaphwan::print_strongkick_kaphwan(HDC mDC)
{
	img_right = img_left + strongkick_kaphwan.strongkick_ani[strongkick_kaphwan.ani_index].img_width;
	img_bottom = img_top + strongkick_kaphwan.strongkick_ani[strongkick_kaphwan.ani_index].img_height;

	if (strongkick_kaphwan.ani_index == 3 || strongkick_kaphwan.ani_index == 4) {
		strongkick_kaphwan.hitbox.left = img_left - 108;
		strongkick_kaphwan.hitbox.top = img_top + 12;
		strongkick_kaphwan.hitbox.right = img_left - 78;
		strongkick_kaphwan.hitbox.bottom = img_top + 47;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		strongkick_kaphwan.hitbox.left = -1000;
		strongkick_kaphwan.hitbox.top = -1000;
		strongkick_kaphwan.hitbox.right = -1000;
		strongkick_kaphwan.hitbox.bottom = -1000;
	}

	strongkick_kaphwan.strongkick_ani[strongkick_kaphwan.ani_index].img.TransparentBlt(mDC, img_left - 108, img_top, img_right - img_left, img_bottom - img_top, 0, 0, strongkick_kaphwan.strongkick_ani[strongkick_kaphwan.ani_index].img_width, strongkick_kaphwan.strongkick_ani[strongkick_kaphwan.ani_index].img_height, RGB(8, 49, 132));

}

void Kaphwan::print_standinghit_kaphwan(HDC mDC) {
	img_right = img_left + standinghit_kaphwan.standinghit_ani[standinghit_kaphwan.ani_index].img_width;
	img_bottom = img_top + standinghit_kaphwan.standinghit_ani[standinghit_kaphwan.ani_index].img_height;
	standinghit_kaphwan.standinghit_ani[standinghit_kaphwan.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, standinghit_kaphwan.standinghit_ani[standinghit_kaphwan.ani_index].img_width, standinghit_kaphwan.standinghit_ani[standinghit_kaphwan.ani_index].img_height, RGB(8, 49, 132));
}

void Kaphwan::print_sittinghit_kaphwan(HDC mDC) {
	img_right = img_left + sittinghit_kaphwan.sittinghit_ani[sittinghit_kaphwan.ani_index].img_width;
	img_bottom = img_top + sittinghit_kaphwan.sittinghit_ani[sittinghit_kaphwan.ani_index].img_height;
	sittinghit_kaphwan.sittinghit_ani[sittinghit_kaphwan.ani_index].img.TransparentBlt(mDC, img_left + 14, img_top, img_right - img_left, img_bottom - img_top, 0, 0, sittinghit_kaphwan.sittinghit_ani[sittinghit_kaphwan.ani_index].img_width, sittinghit_kaphwan.sittinghit_ani[sittinghit_kaphwan.ani_index].img_height, RGB(8, 49, 132));
}

void Kaphwan::print_jumphit_kaphwan(HDC mDC) {
	img_right = img_left + jumphit_kaphwan.jumphit_ani[jumphit_kaphwan.ani_index].img_width;
	img_bottom = img_top + jumphit_kaphwan.jumphit_ani[jumphit_kaphwan.ani_index].img_height;
	jumphit_kaphwan.jumphit_ani[jumphit_kaphwan.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, jumphit_kaphwan.jumphit_ani[jumphit_kaphwan.ani_index].img_width, jumphit_kaphwan.jumphit_ani[jumphit_kaphwan.ani_index].img_height, RGB(8, 49, 132));
}

void Kaphwan::print_sittingpunch_kaphwan(HDC mDC) {
	img_right = img_left + sittingpunch_kaphwan.sittingpunch_ani[sittingpunch_kaphwan.ani_index].img_width;
	img_bottom = img_top + sittingpunch_kaphwan.sittingpunch_ani[sittingpunch_kaphwan.ani_index].img_height;

	if (sittingpunch_kaphwan.ani_index == 1 || sittingpunch_kaphwan.ani_index == 2) {
		sittingpunch_kaphwan.hitbox.left = img_left - 33;
		sittingpunch_kaphwan.hitbox.top = img_top + 120;
		sittingpunch_kaphwan.hitbox.right = img_left - 13;
		sittingpunch_kaphwan.hitbox.bottom = img_top + 140;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		sittingpunch_kaphwan.hitbox.left = -1000;
		sittingpunch_kaphwan.hitbox.top = -1000;
		sittingpunch_kaphwan.hitbox.right = -1000;
		sittingpunch_kaphwan.hitbox.bottom = -1000;
	}

	sittingpunch_kaphwan.sittingpunch_ani[sittingpunch_kaphwan.ani_index].img.TransparentBlt(mDC, img_left - 72, img_top, img_right - img_left, img_bottom - img_top, 0, 0, sittingpunch_kaphwan.sittingpunch_ani[sittingpunch_kaphwan.ani_index].img_width, sittingpunch_kaphwan.sittingpunch_ani[sittingpunch_kaphwan.ani_index].img_height, RGB(8, 49, 132));
}

void Kaphwan::print_sittingkick_kaphwan(HDC mDC) {
	img_right = img_left + sittingkick_kaphwan.sittingkick_ani[sittingkick_kaphwan.ani_index].img_width;
	img_bottom = img_top + sittingkick_kaphwan.sittingkick_ani[sittingkick_kaphwan.ani_index].img_height;

	if (sittingkick_kaphwan.ani_index == 1 || sittingkick_kaphwan.ani_index == 2) {
		sittingkick_kaphwan.hitbox.left = img_left - 35;
		sittingkick_kaphwan.hitbox.top = img_top + 204;
		sittingkick_kaphwan.hitbox.right = img_left - 5;
		sittingkick_kaphwan.hitbox.bottom = img_top + 224;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		sittingkick_kaphwan.hitbox.left = -1000;
		sittingkick_kaphwan.hitbox.top = -1000;
		sittingkick_kaphwan.hitbox.right = -1000;
		sittingkick_kaphwan.hitbox.bottom = -1000;
	}

	sittingkick_kaphwan.sittingkick_ani[sittingkick_kaphwan.ani_index].img.TransparentBlt(mDC, img_left - 72, img_top, img_right - img_left, img_bottom - img_top, 0, 0, sittingkick_kaphwan.sittingkick_ani[sittingkick_kaphwan.ani_index].img_width, sittingkick_kaphwan.sittingkick_ani[sittingkick_kaphwan.ani_index].img_height, RGB(8, 49, 132));
}

void Kaphwan::print_jumppunch_kaphwan(HDC mDC) {
	img_right = img_left + jumppunch_kaphwan.jumppunch_ani[jumppunch_kaphwan.ani_index].img_width;
	img_bottom = img_top + jumppunch_kaphwan.jumppunch_ani[jumppunch_kaphwan.ani_index].img_height;

	if (jumppunch_kaphwan.ani_index == 2 || jumppunch_kaphwan.ani_index == 3) {
		jumppunch_kaphwan.hitbox.left = img_left - 58;
		jumppunch_kaphwan.hitbox.top = img_top + 65;
		jumppunch_kaphwan.hitbox.right = img_left - 33;
		jumppunch_kaphwan.hitbox.bottom = img_top + 85;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		jumppunch_kaphwan.hitbox.left = -1000;
		jumppunch_kaphwan.hitbox.top = -1000;
		jumppunch_kaphwan.hitbox.right = -1000;
		jumppunch_kaphwan.hitbox.bottom = -1000;
	}

	jumppunch_kaphwan.jumppunch_ani[jumppunch_kaphwan.ani_index].img.TransparentBlt(mDC, img_left - 72, img_top, img_right - img_left, img_bottom - img_top, 0, 0, jumppunch_kaphwan.jumppunch_ani[jumppunch_kaphwan.ani_index].img_width, jumppunch_kaphwan.jumppunch_ani[jumppunch_kaphwan.ani_index].img_height, RGB(8, 49, 132));
}

void Kaphwan::print_jumpkick_kaphwan(HDC mDC) {
	img_right = img_left + jumpkick_kaphwan.jumpkick_ani[jumpkick_kaphwan.ani_index].img_width;
	img_bottom = img_top + jumpkick_kaphwan.jumpkick_ani[jumpkick_kaphwan.ani_index].img_height;

	if (jumpkick_kaphwan.ani_index == 2 || jumpkick_kaphwan.ani_index == 3) {
		jumpkick_kaphwan.hitbox.left = img_left - 64;
		jumpkick_kaphwan.hitbox.top = img_top + 120;
		jumpkick_kaphwan.hitbox.right = img_left - 33;
		jumpkick_kaphwan.hitbox.bottom = img_top + 140;

		hitbox.left = -5000;
		hitbox.top = -5000;
		hitbox.right = -5000;
		hitbox.bottom = -5000;
	}
	else {
		jumpkick_kaphwan.hitbox.left = -1000;
		jumpkick_kaphwan.hitbox.top = -1000;
		jumpkick_kaphwan.hitbox.right = -1000;
		jumpkick_kaphwan.hitbox.bottom = -1000;
	}

	jumpkick_kaphwan.jumpkick_ani[jumpkick_kaphwan.ani_index].img.TransparentBlt(mDC, img_left - 81, img_top, img_right - img_left, img_bottom - img_top, 0, 0, jumpkick_kaphwan.jumpkick_ani[jumpkick_kaphwan.ani_index].img_width, jumpkick_kaphwan.jumpkick_ani[jumpkick_kaphwan.ani_index].img_height, RGB(8, 49, 132));
}