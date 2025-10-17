#include "IMAGE.h"
#include <iostream>
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

IMAGE::IMAGE() {};
IMAGE::~IMAGE() {};

void IMAGE::ImageInitialize() {
	img_width = img.GetWidth();
	img_height = img.GetHeight();

	std::cout << "이미지마다 폭, 높이값 초기화됨" << std::endl;
}