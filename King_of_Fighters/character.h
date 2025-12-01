#pragma once
#include "action.h"
#include "player.h"

class Character : public PLAYER {
public:
	ACTION* action;

public:
	Character();
	~Character() = default;

	//void initialize();
};