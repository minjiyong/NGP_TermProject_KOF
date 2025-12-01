#pragma once
#include <windows.h>
#include <atlImage.h>
#include "IMAGE.h"
#include "Effect.h"

Effect::Effect() {};
Effect::~Effect() {};

void Effect::Initialize_effect() {
	hit.hit_img_load();
	for (int i = 0; i < 10; ++i) {
		hit.hit_ani[i].ImageInitialize();
	}

	guard.guard_img_load();
	for (int i = 0; i < 10; ++i) {
		guard.guard_ani[i].ImageInitialize();
	}
}

void Effect::print_hit(HDC mDC) {
	img_right = img_left + hit.hit_ani[hit.ani_index].img_width;
	img_bottom = img_top + hit.hit_ani[hit.ani_index].img_height;
	hit.hit_ani[hit.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, hit.hit_ani[hit.ani_index].img_width, hit.hit_ani[hit.ani_index].img_height, RGB(0, 0, 0));
}

void Effect::print_guard(HDC mDC) {
	img_right = img_left + hit.hit_ani[hit.ani_index].img_width;
	img_bottom = img_top + hit.hit_ani[hit.ani_index].img_height;
	guard.guard_ani[guard.ani_index].img.TransparentBlt(mDC, img_left, img_top, img_right - img_left, img_bottom - img_top, 0, 0, guard.guard_ani[guard.ani_index].img_width, guard.guard_ani[guard.ani_index].img_height, RGB(9, 0, 0));
}