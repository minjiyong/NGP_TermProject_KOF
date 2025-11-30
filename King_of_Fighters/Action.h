#pragma once
#include "headers.h"
#include "HitBox.h"   // 새로 만든 헤더

class IMAGE;

class Action
{
public:
    IMAGE* image;
	HitBox HurtBox;  // 이 액션의 기본 피격 히트박스
    std::vector<FrameHitBoxes> frames;
    // 이 액션을 구성하는 프레임별 히트박스 정보
    int  Totalframecnt;  // 총 프레임 수

    void print();

    const FrameHitBoxes* getFrame(int frameIndex) const;
    void addFrameHitBoxes(const FrameHitBoxes& f);

    Action();
    ~Action();
};

Action::Action()
{
    image = nullptr;
    Totalframecnt = 0;
}

Action::~Action()
{
}

const FrameHitBoxes* Action::getFrame(int frameIndex) const
{
    for (const FrameHitBoxes& f : frames)
        if (f.frameIndex == frameIndex)
            return &f;
    return nullptr;
}

