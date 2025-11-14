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

void SOUND::setSoundFile(LPCWSTR file) {
	soundFile = file; // wstring에 안전하게 복사
}

void SOUND::playSound() {
	// Implementation for playing sound
	PlaySound(soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}