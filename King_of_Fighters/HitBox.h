#pragma once
#pragma once
#include "headers.h"

// 히트박스 종류
enum class HitBoxType : unsigned char
{
    Hurt,   // 피격 판정 (몸통)
    Attack, // 공격 판정
};

struct HitBox
{
    HitBoxType type;
    RECT       rect;  // { left, top, right, bottom } in local space
    bool is_active = true; // 히트박스 활성화 여부
};

// 한 프레임에서 사용할 히트박스 모음
struct FrameHitBoxes
{
    int frameIndex;               // 이 액션 내에서의 프레임 인덱스
    std::vector<HitBox> boxes;    // 그 프레임에 존재하는 모든 hit 박스
};
