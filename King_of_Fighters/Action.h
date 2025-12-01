#pragma once
#include "headers.h"
#include "image.h"
#include "HitBox.h"   // 새로 만든 헤더

class ACTION
{
public:
    IMAGE* image;
	HITBOX HurtBox;  // 이 액션의 기본 피격 히트박스
    std::vector<FrameHitBoxes> frames;
    // 이 액션을 구성하는 프레임별 히트박스 정보
    int  Totalframecnt;  // 총 프레임 수

    ACTION();
    ~ACTION();

    const FrameHitBoxes* getFrame(int frameIndex) const;
    //void addFrameHitBoxes(const FrameHitBoxes& f);
    void initImages();
};

ACTION MakeRectAction(int totalFrames,
    HITBOXTYPE type,
    LONG left, LONG top, LONG right, LONG bottom);

ACTION MakeHurtAction(int totalFrames,
    LONG left, LONG top, LONG right, LONG bottom);

ACTION MakeAttackAction(int totalFrames,
    LONG left, LONG top, LONG right, LONG bottom);