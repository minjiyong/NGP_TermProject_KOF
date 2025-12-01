#include "chin.h"

constexpr int CHIN_ACTION_CNT = 20;

Chin::Chin()
{

}

void Chin::init()
{
    action = new ACTION[CHIN_ACTION_CNT]();
    const RECT commonHurtBox = { 12, 0, 91, 191 };

    action[PS_Idle].Totalframecnt = 9; // V
    action[PS_CrouchIdle].Totalframecnt = 1; // V
    action[PS_JumpIdle].Totalframecnt = 11; // 사진 4개
    //------------------------------
    action[PS_BackMove].Totalframecnt = 5; // V
    action[PS_ForwardMove].Totalframecnt = 7; // V
    action[PS_JumpBackMove].Totalframecnt = 11; // 사진 4개
    action[PS_JumpForwardMove].Totalframecnt = 11; // 사진 4개
    //------------------------------
    action[PS_standguard].Totalframecnt = 3; // 사진 1개
    action[PS_crouchguard].Totalframecnt = 3; // 사진 1개
    //------------------------------
    action[PS_standhit].Totalframecnt = 4; // 사진 1개
    action[PS_crouchhit].Totalframecnt = 4; // 사진 3개
    action[PS_jumphit].Totalframecnt = 7; // 사진 6개
    //------------------------------
    action[PS_punch_crouch].Totalframecnt = 4; // 사진 2개
    action[PS_punch_jump].Totalframecnt = 6; // 사진 3개
    action[PS_kick_crouch].Totalframecnt = 6; // 사진 3개
    action[PS_kick_jump].Totalframecnt = 6; // 사진 3개
    //------------------------------
    action[PS_punch_weak].Totalframecnt = 4; // 사진 2개
    action[PS_punch_strong].Totalframecnt = 6; // 사진 3개z
    action[PS_kick_weak].Totalframecnt = 5; // 사진 2개
    action[PS_kick_strong].Totalframecnt = 8; // 사진 5개
    //------------------------------

    // 모든 Action에 공통 피격 히트박스 적용
    for (int i = 0; i < 20; i++)
    {
        action[i].HurtBox.type = HITBOXTYPE::Hurt;
        action[i].HurtBox.rect = commonHurtBox;
        action[i].initImages(); // Image 갯수대로 Image 객체 생성
    }

    std::wstring fileName;

    // 이미지 로드
    for (int i = 0; i < action[PS_Idle].Totalframecnt; ++i) {
        fileName = L"image/Chin_Idle_" + std::to_wstring(i) + L".png";
        action[PS_Idle].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }

    for (int i = 0; i < action[PS_CrouchIdle].Totalframecnt; ++i) {
        fileName = L"image/Chin_CrouchIdle_" + std::to_wstring(i) + L".png";
        action[PS_CrouchIdle].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }
    //
    //for (int i = 0; i < action[PS_JumpIdle].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_JumpIdle_" + std::to_wstring(i) + L".png";
    //    action[PS_JumpIdle].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    ////------------------------------
    for (int i = 0; i < action[PS_BackMove].Totalframecnt; ++i) {
        fileName = L"image/Chin_BackMove_" + std::to_wstring(i) + L".png";
        action[PS_BackMove].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }
    //
    for (int i = 0; i < action[PS_ForwardMove].Totalframecnt; ++i) {
        fileName = L"image/Chin_ForwardMove_" + std::to_wstring(i) + L".png";
        action[PS_ForwardMove].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }
    //
    //// 점프 이미지 돌려쓸거라 JumpIdle 이미지 할당
    //for (int i = 0; i < action[PS_JumpBackMove].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_JumpIdle_" + std::to_wstring(i) + L".png";
    //    action[PS_JumpBackMove].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_JumpForwardMove].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_JumpIdle_" + std::to_wstring(i) + L".png";
    //    action[PS_JumpForwardMove].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    ////------------------------------
    //for (int i = 0; i < action[PS_standguard].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_StandGuard_" + std::to_wstring(i) + L".png";
    //    action[PS_standguard].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_crouchguard].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_CrouchGuard_" + std::to_wstring(i) + L".png";
    //    action[PS_crouchguard].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    ////------------------------------
    //for (int i = 0; i < action[PS_standhit].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_StandHit_" + std::to_wstring(i) + L".png";
    //    action[PS_standhit].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_crouchhit].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_CrouchHit_" + std::to_wstring(i) + L".png";
    //    action[PS_crouchhit].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_jumphit].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_JumpHit_" + std::to_wstring(i) + L".png";
    //    action[PS_jumphit].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    ////------------------------------
    //for (int i = 0; i < action[PS_punch_crouch].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_Punch_Crouch_" + std::to_wstring(i) + L".png";
    //    action[PS_punch_crouch].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_punch_jump].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_Punch_Jump_" + std::to_wstring(i) + L".png";
    //    action[PS_punch_jump].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_kick_crouch].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_Kick_Crouch_" + std::to_wstring(i) + L".png";
    //    action[PS_kick_crouch].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_kick_jump].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_Kick_Jump_" + std::to_wstring(i) + L".png";
    //    action[PS_kick_jump].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    ////------------------------------
    //for (int i = 0; i < action[PS_punch_weak].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_Punch_Weak_" + std::to_wstring(i) + L".png";
    //    action[PS_punch_weak].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_punch_strong].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_Punch_Strong_" + std::to_wstring(i) + L".png";
    //    action[PS_punch_strong].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_kick_weak].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_Kick_Weak_" + std::to_wstring(i) + L".png";
    //    action[PS_kick_weak].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}
    //
    //for (int i = 0; i < action[PS_kick_strong].Totalframecnt; ++i) {
    //    fileName = L"image/Chin_Kick_Strong_" + std::to_wstring(i) + L".png";
    //    action[PS_kick_strong].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    //}

    std::cout << "Chin image load complete\n" << std::endl;

    // 히트박스 생성
    action[PS_punch_crouch] = // 1,2 피격타이밍
        MakeAttackAction(
            4,
            135 - 20, 332 + 101,
            135 + 0, 332 + 122
        );

    action[PS_punch_jump] = // 2,3 피격타이밍
        MakeAttackAction(
            6,
            135 - 15, 332 + 135,
            135 + 5, 332 + 157
        );
    //------------------------------
    action[PS_kick_crouch] = // 2, 3 피격타이밍
        MakeAttackAction(
            6,
            135 - 60, 332 + 173,
            135 - 27, 332 + 191
        );

    action[PS_kick_jump] = // 2, 3 피격타이밍
        MakeAttackAction(
            6,
            135 - 70, 332 + 53,
            135 - 42, 332 + 90
        );
    //------------------------------
    action[PS_punch_weak] = // 1,2 피격타이밍
        MakeAttackAction(
            4,
            135 - 7, 332 + 60,
            135 + 19, 332 + 82
        );

    action[PS_punch_strong] = // 2,3 피격타이밍
        MakeAttackAction(
            5,
            135 - 16, 332 + 54,
            135 + 10, 332 + 74
        );
    //------------------------------
    action[PS_kick_weak] = // 1,2 피격타이밍
        MakeAttackAction(
            5,
            135 - 60, 332 + 83,
            135 - 27, 332 + 107
        );

    action[PS_kick_strong] = // 4,5 피격타이밍
        MakeAttackAction(
            8,
            135 - 70, 332 + 109,
            135 - 39, 332 + 131
        );
}

void Chin::print(HDC& hdc) {
    if (p_state == PS_Idle || p_state == PS_CrouchIdle || p_state == PS_ForwardMove || p_state == PS_BackMove)
    {
		IMAGE temp_img = action[p_state].image[ani_index & action[p_state].Totalframecnt];
        temp_img._img.TransparentBlt(hdc, x_pos, y_pos,
            temp_img._width, temp_img._height, 0, 0,
            temp_img._left, temp_img._top,
            RGB(8, 0, 99));
        //if (ani_index == action[p_state].Totalframecnt)
        //{
		//	ani_index = 0;
        //}
    }
    else
    {
        IMAGE temp_img = action[p_state].image[ani_index & action[p_state].Totalframecnt];
        temp_img._img.TransparentBlt(hdc, x_pos, y_pos,
            temp_img._width, temp_img._height, 0, 0,
            temp_img._left, temp_img._top,
            RGB(8, 0, 99));
        //if (ani_index == action[p_state].Totalframecnt)
        //{
        //    ani_index = 0;
		//	p_state = PS_Idle;
        //}
    }
}