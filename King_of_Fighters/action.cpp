#include "action.h"

ACTION::ACTION()
{
    image = nullptr;
    Totalframecnt = 0;
}

ACTION::~ACTION()
{
}

void ACTION::initImages()
{
	// 이미지 초기화 코드 작성
    image = new IMAGE[Totalframecnt]();
}