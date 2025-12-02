#include "action.h"

ACTION::ACTION()
{
    image = nullptr;
    Totalframecnt = 0;
}

ACTION::~ACTION()
{
}

const FrameHitBoxes* ACTION::getFrame(int frameIndex) const
{
    for (const FrameHitBoxes& f : frames)
        if (f.frameIndex == frameIndex)
            return &f;
    return nullptr;
}

void ACTION::initImages()
{
	// 이미지 초기화 코드 작성
    image = new IMAGE[Totalframecnt]();
}

// ---------------- 공통 초기화 함수 ----------------
// totalFrames 개의 프레임을 만들고,
// 각 프레임에 동일한 RECT 히트박스 1개를 넣는 함수
ACTION MakeRectAction(int totalFrames,
    HITBOXTYPE type,
    LONG left, LONG top, LONG right, LONG bottom)
{
    ACTION a;
    a.Totalframecnt = totalFrames;
    a.frames.clear();
    a.frames.reserve(totalFrames);

    for (int i = 0; i < totalFrames; ++i)
    {
        FrameHitBoxes fh;
        fh.frameIndex = i;

        HITBOX hb;
        hb.type = type;
        hb.rect.left = left;
        hb.rect.top = top;
        hb.rect.right = right;
        hb.rect.bottom = bottom;
        hb.is_active = true;

        fh.boxes.push_back(hb);
        a.frames.push_back(std::move(fh));
    }

    return a;
}

// 타입까지 상수로 넣기 귀찮으면, 타입 고정 래퍼 두 개 만들어도 됨
ACTION MakeHurtAction(int totalFrames,
    LONG left, LONG top, LONG right, LONG bottom)
{
    return MakeRectAction(totalFrames, HITBOXTYPE::Hurt,
        left, top, right, bottom);
}

ACTION MakeAttackAction(int totalFrames,
    LONG left, LONG top, LONG right, LONG bottom)
{
    return MakeRectAction(totalFrames, HITBOXTYPE::Attack,
        left, top, right, bottom);
}
