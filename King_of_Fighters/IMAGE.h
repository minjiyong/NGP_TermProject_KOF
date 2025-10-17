#pragma once
#include <atlImage.h>

class IMAGE {
public:
	CImage img{};
	int img_width{};
	int img_height{};

	IMAGE();
	~IMAGE();

	void ImageInitialize();
};