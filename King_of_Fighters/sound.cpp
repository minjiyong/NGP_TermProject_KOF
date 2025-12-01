#include "sound.h"

void SOUND::setSoundFile(LPCWSTR file) {
	soundFile = file; // wstring에 안전하게 복사
}

void SOUND::playSound() {
	// Implementation for playing sound
	PlaySound(soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}