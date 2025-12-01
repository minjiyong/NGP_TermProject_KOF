#pragma once
#include "character.h"
#include "action.h"

class Chin : public Character {
public:
	Chin();
	~Chin() = default;

public:
	void init();
	void print(HDC& hdc);
};