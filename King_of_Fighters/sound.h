#pragma once
#include "headers.h"

class SOUND {
public:
	std::wstring soundFile;

public:
	SOUND() = default;
	~SOUND() = default;

	void setSoundFile(LPCWSTR file);
	void playSound();
};