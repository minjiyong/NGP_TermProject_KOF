// Character.h
#pragma once
#include <windows.h>
#include <cstdint>

enum CHARACTER_TYPE : std::int32_t
{
    CT_CHIN = 0,
    CT_KAP = 1,
    // 다른 캐릭터 추가 예정이면 여기 확장
};

struct CharacterState
{
    std::int32_t id{};       // 서버에서 부여하는 플레이어 ID (0~2 등)
    CHARACTER_TYPE type{ CT_CHIN };

    // 위치 (Chin의 img_left / img_top 를 그대로 맵핑)
    std::int32_t x{};        // 왼쪽 상단 X
    std::int32_t y{};        // 왼쪽 상단 Y

    // HP
    std::int32_t hp{ 1000 };
    std::int32_t max_hp{ 1000 };

    // 기존 condition1 / 2 / 3 그대로 노출
    // (STANDING, JUMP, NOATTACK, FRONTMOVE, NOHIT, HITTED, GUARD 등)
    std::int32_t condition1{};  // 자세 (STANDING / JUMP / SITTING ...)
    std::int32_t condition2{};  // 이동/공격 상태 (NOATTACK / FRONTMOVE / BACKMOVE / WEAKPUNCH ...)
    std::int32_t condition3{};  // 피격/가드 상태 (NOHIT / HITTED / GUARD ...)

    // 판정 박스
    RECT body_box{};    // 몸(피격) 판정
    RECT attack_box{};  // 현재 유효한 공격 판정(없으면 빈 박스)
};
