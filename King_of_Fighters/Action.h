#pragma once
#include "headers.h"
#include "image.h"
#include "HitBox.h"   // 새로 만든 헤더

class ACTION
{
public:
    IMAGE* image;
    std::vector<FrameHitBoxes> frames;
    // 이 액션을 구성하는 프레임별 히트박스 정보
    int  Totalframecnt;  // 총 프레임 수

    ACTION();
    ~ACTION();

    void initImages();
};