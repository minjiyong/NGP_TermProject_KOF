#include "chin.h"
#include "hitbox.h"
constexpr int CHIN_ACTION_CNT = 20;

Chin::Chin()
{
    p_state = PS_Idle;
}

void Chin::init()
{
    action = new ACTION[CHIN_ACTION_CNT]();

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
        action[i].initImages(); // Image 갯수대로 Image 객체 생성
        //std::cout << "action[" << i << "] image init" << std::endl;
    }

    std::wstring fileName;
    std::wstring fileName1;
    std::wstring fileName2;
    std::wstring fileName3;
    std::wstring fileName4;
    std::wstring fileName5;

    // 이미지 로드
    for (int i = 0; i < action[PS_Idle].Totalframecnt; ++i) {
        fileName = L"image/Chin_Idle_" + std::to_wstring(i) + L".png";
        action[PS_Idle].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }

    //std::cout << "action[" << PS_Idle << "] image load" << std::endl;

    for (int i = 0; i < action[PS_CrouchIdle].Totalframecnt; ++i) {
        fileName = L"image/Chin_CrouchIdle_" + std::to_wstring(i) + L".png";
        action[PS_CrouchIdle].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }

    //std::cout << "action[" << PS_CrouchIdle << "] image load" << std::endl;

    // JumpIdle, JumpBackMove, JumpForwardMove
    fileName = L"image/Chin_JumpIdle_0.png";
    fileName1 = L"image/Chin_JumpIdle_1.png";
    fileName2 = L"image/Chin_JumpIdle_2.png";
    fileName3 = L"image/Chin_JumpIdle_3.png";

    action[PS_JumpIdle].image[0].SetImage(fileName.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[1].SetImage(fileName1.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[2].SetImage(fileName2.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[3].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[4].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[5].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[6].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[7].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[8].SetImage(fileName2.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[9].SetImage(fileName1.c_str(), -20, 0, 0, 0);
    action[PS_JumpIdle].image[10].SetImage(fileName.c_str(), -20, 0, 0, 0);

    //std::cout << "action[" << PS_JumpIdle << "] image load" << std::endl;

    for (int i = 0; i < action[PS_BackMove].Totalframecnt; ++i) {
        fileName = L"image/Chin_BackMove_" + std::to_wstring(i) + L".png";
        action[PS_BackMove].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }

    //std::cout << "action[" << PS_BackMove << "] image load" << std::endl;

    for (int i = 0; i < action[PS_ForwardMove].Totalframecnt; ++i) {
        fileName = L"image/Chin_ForwardMove_" + std::to_wstring(i) + L".png";
        action[PS_ForwardMove].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }

    //std::cout << "action[" << PS_ForwardMove << "] image load" << std::endl;


    action[PS_JumpBackMove].image[0].SetImage(fileName.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[1].SetImage(fileName1.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[2].SetImage(fileName2.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[3].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[4].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[5].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[6].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[7].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[8].SetImage(fileName2.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[9].SetImage(fileName1.c_str(), -20, 0, 0, 0);
    action[PS_JumpBackMove].image[10].SetImage(fileName.c_str(), -20, 0, 0, 0);

    //std::cout << "action[" << PS_JumpBackMove << "] image load" << std::endl;

    action[PS_JumpForwardMove].image[0].SetImage(fileName.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[1].SetImage(fileName1.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[2].SetImage(fileName2.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[3].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[4].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[5].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[6].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[7].SetImage(fileName3.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[8].SetImage(fileName2.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[9].SetImage(fileName1.c_str(), -20, 0, 0, 0);
    action[PS_JumpForwardMove].image[10].SetImage(fileName.c_str(), -20, 0, 0, 0);

    //std::cout << "action[" << PS_JumpForwardMove << "] image load" << std::endl;

    for (int i = 0; i < action[PS_standguard].Totalframecnt; ++i) {
        fileName = L"image/Chin_StandGuard_0.png";
        action[PS_standguard].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }

    //std::cout << "action[" << PS_standguard << "] image load" << std::endl;

    for (int i = 0; i < action[PS_crouchguard].Totalframecnt; ++i) {
        fileName = L"image/Chin_CrouchGuard_0.png";
        action[PS_crouchguard].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }

    //std::cout << "action[" << PS_crouchguard << "] image load" << std::endl;

    //------------------------------
    for (int i = 0; i < action[PS_standhit].Totalframecnt; ++i) {
        fileName = L"image/Chin_StandHit_0.png";
        action[PS_standhit].image[i].SetImage(fileName.c_str(), 0, 0, 0, 0);
    }

    //std::cout << "action[" << PS_standhit << "] image load" << std::endl;

    // crouchhit
    fileName = L"image/Chin_CrouchHit_0.png";
    fileName1 = L"image/Chin_CrouchHit_1.png";
    fileName2 = L"image/Chin_CrouchHit_2.png";

    action[PS_crouchhit].image[0].SetImage(fileName.c_str(), 0, 0, 0, 0);
    action[PS_crouchhit].image[1].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_crouchhit].image[2].SetImage(fileName2.c_str(), 0, 0, 0, 0);
    action[PS_crouchhit].image[3].SetImage(fileName2.c_str(), 0, 0, 0, 0);

    //std::cout << "action[" << PS_crouchhit << "] image load" << std::endl;

    // jumphit
    fileName = L"image/Chin_JumpHit_0.png";
    fileName1 = L"image/Chin_JumpHit_1.png";
    fileName2 = L"image/Chin_JumpHit_2.png";
    fileName3 = L"image/Chin_JumpHit_3.png";
    fileName4 = L"image/Chin_JumpHit_4.png";
    fileName5 = L"image/Chin_JumpHit_5.png";

    action[PS_jumphit].image[0].SetImage(fileName.c_str(), 0, 0, 0, 0);
    action[PS_jumphit].image[1].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_jumphit].image[2].SetImage(fileName2.c_str(), 0, 0, 0, 0);
    action[PS_jumphit].image[3].SetImage(fileName3.c_str(), 0, 0, 0, 0);
    action[PS_jumphit].image[4].SetImage(fileName4.c_str(), 0, 0, 0, 0);
    action[PS_jumphit].image[5].SetImage(fileName5.c_str(), 0, 0, 0, 0);
    action[PS_jumphit].image[6].SetImage(fileName5.c_str(), 0, 0, 0, 0);

    //std::cout << "action[" << PS_jumphit << "] image load" << std::endl;

    //------------------------------
    // punch_crouch
    fileName = L"image/Chin_Punch_Crouch_0.png";
    fileName1 = L"image/Chin_Punch_Crouch_1.png";

    //

    action[PS_punch_crouch].image[0].SetImage(fileName.c_str(), 0, 0, 0, 0);
    action[PS_punch_crouch].image[1].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_punch_crouch].image[2].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_punch_crouch].image[3].SetImage(fileName.c_str(), 0, 0, 0, 0);

    //std::cout << "action[" << PS_punch_crouch << "] image load" << std::endl;

    // punch_jump
    fileName = L"image/Chin_Punch_Jump_0.png";
    fileName1 = L"image/Chin_Punch_Jump_1.png";
    fileName2 = L"image/Chin_Punch_Jump_2.png";

    action[PS_punch_jump].image[0].SetImage(fileName.c_str(), 10, 0, 0, 0);
    action[PS_punch_jump].image[1].SetImage(fileName1.c_str(), 10, 0, 0, 0);
    action[PS_punch_jump].image[2].SetImage(fileName2.c_str(), 10, 0, 0, 0);
    action[PS_punch_jump].image[3].SetImage(fileName2.c_str(), 10, 0, 0, 0);
    action[PS_punch_jump].image[4].SetImage(fileName1.c_str(), 10, 0, 0, 0);
    action[PS_punch_jump].image[5].SetImage(fileName.c_str(), 10, 0, 0, 0);

    //std::cout << "action[" << PS_punch_jump << "] image load" << std::endl;

    // kick_crouch
    fileName = L"image/Chin_Kick_Crouch_0.png";
    fileName1 = L"image/Chin_Kick_Crouch_1.png";
    fileName2 = L"image/Chin_Kick_Crouch_2.png";

    action[PS_kick_crouch].image[0].SetImage(fileName.c_str(), 0, 0, 0, 0);
    action[PS_kick_crouch].image[1].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_kick_crouch].image[2].SetImage(fileName2.c_str(), 0, 0, 0, 0);
    action[PS_kick_crouch].image[3].SetImage(fileName2.c_str(), 0, 0, 0, 0);
    action[PS_kick_crouch].image[4].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_kick_crouch].image[5].SetImage(fileName.c_str(), 0, 0, 0, 0);

    //std::cout << "action[" << PS_kick_crouch << "] image load" << std::endl;

    // kick_jump
    fileName = L"image/Chin_Kick_Jump_0.png";
    fileName1 = L"image/Chin_Kick_Jump_1.png";
    fileName2 = L"image/Chin_Kick_Jump_2.png";

    action[PS_kick_jump].image[0].SetImage(fileName.c_str(), 0, 0, 0, 0);
    action[PS_kick_jump].image[1].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_kick_jump].image[2].SetImage(fileName2.c_str(), 0, 0, 0, 0);
    action[PS_kick_jump].image[3].SetImage(fileName2.c_str(), 0, 0, 0, 0);
    action[PS_kick_jump].image[4].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_kick_jump].image[5].SetImage(fileName.c_str(), 0, 0, 0, 0);

    //std::cout << "action[" << PS_kick_jump << "] image load" << std::endl;

    //------------------------------
    // punch_weak
    fileName = L"image/Chin_Punch_Weak_0.png";
    fileName1 = L"image/Chin_Punch_Weak_1.png";

    action[PS_punch_weak].image[0].SetImage(fileName.c_str(), 20, 0, 0, 0);
    action[PS_punch_weak].image[1].SetImage(fileName1.c_str(), 20, 0, 0, 0);
    action[PS_punch_weak].image[2].SetImage(fileName1.c_str(), 20, 0, 0, 0);
    action[PS_punch_weak].image[3].SetImage(fileName.c_str(), 20, 0, 0, 0);

    //std::cout << "action[" << PS_punch_weak << "] image load" << std::endl;

    // punch_strong
    fileName = L"image/Chin_Punch_Strong_0.png";
    fileName1 = L"image/Chin_Punch_Strong_1.png";
    fileName2 = L"image/Chin_Punch_Strong_2.png";

    action[PS_punch_strong].image[0].SetImage(fileName.c_str(), 10, 0, 0, 0);
    action[PS_punch_strong].image[1].SetImage(fileName1.c_str(), 10, 0, 0, 0);
    action[PS_punch_strong].image[2].SetImage(fileName2.c_str(), 10, 0, 0, 0);
    action[PS_punch_strong].image[3].SetImage(fileName2.c_str(), 10, 0, 0, 0);
    action[PS_punch_strong].image[4].SetImage(fileName1.c_str(), 10, 0, 0, 0);
    action[PS_punch_strong].image[5].SetImage(fileName.c_str(), 10, 0, 0, 0);

    //std::cout << "action[" << PS_punch_strong << "] image load" << std::endl;

    // kick_weak
    fileName = L"image/Chin_Kick_Weak_0.png";
    fileName1 = L"image/Chin_Kick_Weak_1.png";

    action[PS_kick_weak].image[0].SetImage(fileName.c_str(), 0, 0, 0, 0);
    action[PS_kick_weak].image[1].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_kick_weak].image[2].SetImage(fileName1.c_str(), 0, 0, 0, 0);
    action[PS_kick_weak].image[3].SetImage(fileName.c_str(), 0, 0, 0, 0);
    action[PS_kick_weak].image[4].SetImage(fileName.c_str(), 0, 0, 0, 0);

    //std::cout << "action[" << PS_kick_weak << "] image load" << std::endl;

    // kick_strong
    fileName = L"image/Chin_Kick_Strong_0.png";
    fileName1 = L"image/Chin_Kick_Strong_1.png";
    fileName2 = L"image/Chin_Kick_Strong_2.png";
    fileName3 = L"image/Chin_Kick_Strong_3.png";
    fileName4 = L"image/Chin_Kick_Strong_4.png";

    action[PS_kick_strong].image[0].SetImage(fileName.c_str(), -40, 0, 0, 0);
    action[PS_kick_strong].image[1].SetImage(fileName1.c_str(), -40, 0, 0, 0);
    action[PS_kick_strong].image[2].SetImage(fileName2.c_str(), -40, 0, 0, 0);
    action[PS_kick_strong].image[3].SetImage(fileName3.c_str(), -40, 0, 0, 0);
    action[PS_kick_strong].image[4].SetImage(fileName4.c_str(), -40, 0, 0, 0);
    action[PS_kick_strong].image[5].SetImage(fileName4.c_str(), -40, 0, 0, 0);
    action[PS_kick_strong].image[6].SetImage(fileName3.c_str(), -40, 0, 0, 0);
    action[PS_kick_strong].image[7].SetImage(fileName2.c_str(), -40, 0, 0, 0);

    //std::cout << "action[" << PS_kick_strong << "] image load" << std::endl;

    std::cout << "Chin image load complete\n" << std::endl;
}

void Chin::print(HDC& hdc) {
    if (p_state == PS_Idle || p_state == PS_CrouchIdle || p_state == PS_ForwardMove || p_state == PS_BackMove)
    {
        action[p_state].image[ani_index]._img.TransparentBlt(hdc, x_pos, y_pos,
            action[p_state].image[ani_index]._width, action[p_state].image[ani_index]._height, 0, 0,
            action[p_state].image[ani_index]._width, action[p_state].image[ani_index]._height,
            RGB(8, 0, 99));
        if (ani_index == action[p_state].Totalframecnt)
        {
            ani_index = 0;
        }
    }
    else
    {
        action[p_state].image[ani_index]._img.TransparentBlt(hdc, x_pos, y_pos,
            action[p_state].image[ani_index]._width, action[p_state].image[ani_index]._height, 0, 0,
            action[p_state].image[ani_index]._width, action[p_state].image[ani_index]._height,
            RGB(8, 0, 99));
        if (ani_index == action[p_state].Totalframecnt)
        {
            ani_index = 0;
            p_state = PS_Idle;
        }
    }
}