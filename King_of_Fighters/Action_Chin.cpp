#pragma once
#include "Action.h"
#define Idle 0
#define CrouchIdle 1
#define JumpIdle 2
//------------------------------
#define BackMove 3
#define ForwardMove 4
#define JumpBackMove 5
#define JumpForwardMove 6
//------------------------------
#define standguard 7
#define crouchguard 8
//------------------------------
#define standhit 9
#define crouchhit 10
#define jumphit 11
//------------------------------
#define punch_crouch 12
#define punch_jump 13
#define kick_crouch 14
#define kick_jump 15
//------------------------------
#define punch_weak 16
#define punch_strong 17
#define kick_weak 18
#define kick_strong 19
std::array<Action,20> Action_Chin;

#include "Action.h"

// ---------------- 공통 초기화 함수 ----------------
// totalFrames 개의 프레임을 만들고,
// 각 프레임에 동일한 RECT 히트박스 1개를 넣는 함수
inline Action MakeRectAction(int totalFrames,
    HitBoxType type,
    LONG left, LONG top, LONG right, LONG bottom)
{
    Action a;
    a.Totalframecnt = totalFrames;
    a.frames.clear();
    a.frames.reserve(totalFrames);

    for (int i = 0; i < totalFrames; ++i)
    {
        FrameHitBoxes fh;
        fh.frameIndex = i;

        HitBox hb;
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
inline Action MakeHurtAction(int totalFrames,
    LONG left, LONG top, LONG right, LONG bottom)
{
    return MakeRectAction(totalFrames, HitBoxType::Hurt,
        left, top, right, bottom);
}

inline Action MakeAttackAction(int totalFrames,
    LONG left, LONG top, LONG right, LONG bottom)
{
    return MakeRectAction(totalFrames, HitBoxType::Attack,
        left, top, right, bottom);
}


void InitChinActions()
{
    const RECT commonHurtBox = { 12, 0, 91, 191 };

    // 모든 Action에 공통 피격 히트박스 적용
    for (Action& act : Action_Chin)
    {
		act.HurtBox.type = HitBoxType::Hurt;
        act.HurtBox.rect = commonHurtBox;
    }
    //------------------------------
    Action_Chin[punch_crouch] = // 1,2 피격타이밍
        MakeAttackAction(
            4,
            135 -20, 332 + 101,
            135 + 0, 332 + 122
        );

	Action_Chin[punch_jump] = // 2,3 피격타이밍
        MakeAttackAction(
            6,
            135 - 15, 332 + 135,
            135 + 5, 332 + 157
        );
    //------------------------------
	Action_Chin[kick_crouch] = // 2, 3 피격타이밍
        MakeAttackAction(
            6,
            135 - 60, 332 + 173,
            135 - 27, 332 + 191
        );

    Action_Chin[kick_jump] = // 2, 3 피격타이밍
        MakeAttackAction(
            6,
            135 - 70, 332 + 53,
            135 - 42, 332 + 90
        );
    //------------------------------
    Action_Chin[punch_weak] = // 1,2 피격타이밍
        MakeAttackAction(
            4,
            135 - 7, 332 + 60,
            135 + 19, 332 + 82
        );

	Action_Chin[punch_strong] = // 2,3 피격타이밍
        MakeAttackAction(
            5,
            135 - 16, 332 + 54,
            135 + 10, 332 + 74
        );
    //------------------------------
    Action_Chin[kick_weak] = // 1,2 피격타이밍
        MakeAttackAction(
            5,
            135 - 60, 332 + 83,
            135 - 27, 332 + 107
        );

	Action_Chin[kick_strong] = // 4,5 피격타이밍
        MakeAttackAction(
            8,
            135 - 70, 332 + 109,
            135 - 39, 332 + 131
        );
    //------------------------------
    Action_Chin[Idle].Totalframecnt = 9;
    Action_Chin[CrouchIdle].Totalframecnt = 1;
    Action_Chin[JumpIdle].Totalframecnt = 11;
    //------------------------------
    Action_Chin[BackMove].Totalframecnt = 5;
    Action_Chin[ForwardMove].Totalframecnt = 7;
    Action_Chin[JumpBackMove].Totalframecnt = 11;
    Action_Chin[JumpForwardMove].Totalframecnt = 11;
    //------------------------------
    Action_Chin[standguard].Totalframecnt = 3;
    Action_Chin[crouchguard].Totalframecnt = 3;
    //------------------------------
    Action_Chin[standhit].Totalframecnt = 4;
    Action_Chin[crouchhit].Totalframecnt = 4;
    Action_Chin[jumphit].Totalframecnt = 7;
    //------------------------------
}
