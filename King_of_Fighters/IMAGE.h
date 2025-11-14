#pragma once
#include "headers.h"

class IMAGE {
public:
	CImage _img{};
	int _width{};
	int _height{};

	int _left{};
	int _top{};
	int _right{};
	int _bottom{};

	IMAGE();
	~IMAGE();

	void SetImage(const wchar_t*, int left, int top, int right, int bottom);
};