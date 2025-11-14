#include "image.h"

IMAGE::IMAGE() {};
IMAGE::~IMAGE() {};

void IMAGE::SetImage(const wchar_t* filename, int left, int top, int right, int bottom) {
	_img.Load(filename);
	_width = _img.GetWidth();
	_height = _img.GetHeight();

	_left = left;
	_top = top;
	_right = right;
	_bottom = bottom;

	std::cout << "이미지 로딩 완료" << std::endl;
}