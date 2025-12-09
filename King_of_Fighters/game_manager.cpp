#include "game_manager.h"

GAMEMANAGER::GAMEMANAGER()
{
}

void GAMEMANAGER::init()
{
	startMusic.setSoundFile(L"character/sound/02-THE-KING-OF-FIGHTERS-_94-Opening-_MVS-Title_.wav");
	ui.SetUI();
}

void GAMEMANAGER::printMap(HDC& mDC) {
	ui.MAP1._img.StretchBlt(mDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ui.MAP1._width, ui.MAP1._height);
	switch (mapTimer) {
	case 0:
		ui.MAP2._img.TransparentBlt(mDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ui.MAP2._width, 
			ui.MAP2._height, RGB(255, 192, 255));
		break;
	case 1:
		ui.MAP3._img.TransparentBlt(mDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ui.MAP3._width, 
			ui.MAP3._height, RGB(255, 192, 255));
		break;
	}
}

void GAMEMANAGER::printHp(HDC& mDC, int p1_hp, int p2_hp, int p3_hp) {
	ui.HP._right = ui.HP._left + ui.HP._width;
	ui.HP._bottom = ui.HP._top + ui.HP._height;
	ui.HP._img.TransparentBlt(mDC, ui.HP._left, ui.HP._top, ui.HP._right - ui.HP._left + 450, 
		ui.HP._bottom - ui.HP._top + 50, 0, 0, ui.HP._width, ui.HP._height, RGB(0, 0, 32));
	
	// p1_HP (Chin)
	draw_rectangle(mDC, 176, 49, 442 - p1_hp, 67, RGB(255, 0, 0));
	// p2_HP (Kap)
	draw_rectangle(mDC, 708, 49, 442 + p2_hp, 67, RGB(255, 0, 0));
	// p3_HP
}

void GAMEMANAGER::printName(HDC& mDC) {
	// P1
	ui.ChinName._right = ui.ChinName._left + ui.ChinName._width;
	ui.ChinName._bottom = ui.ChinName._top + ui.ChinName._height;
	ui.ChinName._img.TransparentBlt(mDC, ui.ChinName._left, ui.ChinName._top, 
		ui.ChinName._right - ui.ChinName._left, ui.ChinName._bottom - ui.ChinName._top, 
		0, 0, ui.ChinName._width, ui.ChinName._height, RGB(57, 81, 57));

	// P2
	ui.ChinName._right = ui.ChinName._left + ui.ChinName._width;
	ui.ChinName._bottom = ui.ChinName._top + ui.ChinName._height;
	ui.ChinName._img.TransparentBlt(mDC, ui.ChinName._left, ui.ChinName._top + 50,
		ui.ChinName._right - ui.ChinName._left, ui.ChinName._bottom - ui.ChinName._top,
		0, 0, ui.ChinName._width, ui.ChinName._height, RGB(57, 81, 57));

	// P3
	ui.ChinName._right = ui.ChinName._left + ui.ChinName._width;
	ui.ChinName._bottom = ui.ChinName._top + ui.ChinName._height;
	ui.ChinName._img.TransparentBlt(mDC, ui.ChinName._left, ui.ChinName._top + 100,
		ui.ChinName._right - ui.ChinName._left, ui.ChinName._bottom - ui.ChinName._top,
		0, 0, ui.ChinName._width, ui.ChinName._height, RGB(57, 81, 57));

	//ui.KapName._right = ui.KapName._left + ui.KapName._width;
	//ui.KapName._bottom = ui.KapName._top + ui.KapName._height;
	//ui.KapName._img.TransparentBlt(mDC, ui.KapName._left, ui.KapName._top, 
	//	ui.KapName._right - ui.KapName._left, ui.KapName._bottom - ui.KapName._top, 
	//	0, 0, ui.KapName._width, ui.KapName._height, RGB(57, 81, 57));
}

void GAMEMANAGER::printProfile(HDC& mDC) {
	// Chin_profile
	// P1
	ui.ChinProfile._right = ui.ChinProfile._left + ui.ChinProfile._width;
	ui.ChinProfile._bottom = ui.ChinProfile._top + ui.ChinProfile._height;
	ui.ChinProfile._img.StretchBlt(mDC, ui.ChinProfile._left, ui.ChinProfile._top, 
		ui.ChinProfile._right - ui.ChinProfile._left, ui.ChinProfile._bottom - ui.ChinProfile._top, 
		0, 0, ui.ChinProfile._width, ui.ChinProfile._height);

	// P2
	ui.ChinProfile._right = ui.ChinProfile._left + ui.ChinProfile._width;
	ui.ChinProfile._bottom = ui.ChinProfile._top + ui.ChinProfile._height;
	ui.ChinProfile._img.StretchBlt(mDC, ui.ChinProfile._left, ui.ChinProfile._top + 50,
		ui.ChinProfile._right - ui.ChinProfile._left, ui.ChinProfile._bottom - ui.ChinProfile._top,
		0, 0, ui.ChinProfile._width, ui.ChinProfile._height);

	// P3
	ui.ChinProfile._right = ui.ChinProfile._left + ui.ChinProfile._width;
	ui.ChinProfile._bottom = ui.ChinProfile._top + ui.ChinProfile._height;
	ui.ChinProfile._img.StretchBlt(mDC, ui.ChinProfile._left, ui.ChinProfile._top + 100,
		ui.ChinProfile._right - ui.ChinProfile._left, ui.ChinProfile._bottom - ui.ChinProfile._top,
		0, 0, ui.ChinProfile._width, ui.ChinProfile._height);

	// Kap_profile
	//ui.KapProfile._right = ui.KapProfile._left + ui.KapProfile._width;
	//ui.KapProfile._bottom = ui.KapProfile._top + ui.KapProfile._height;
	//ui.KapProfile._img.StretchBlt(mDC, ui.KapProfile._left, ui.KapProfile._top, 
	//	ui.KapProfile._right - ui.KapProfile._left, ui.KapProfile._bottom - ui.KapProfile._top, 
	//	0, 0, ui.KapProfile._width, ui.KapProfile._height);


}

void GAMEMANAGER::printTime(HDC& mDC) {
	if (fight >= 5) {
		ui.Time[timeten]._right = ui.Time[timeten]._left + ui.Time[timeten]._width;
		ui.Time[timeten]._bottom = ui.Time[timeten]._top + ui.Time[timeten]._height;
		ui.Time[timeten]._img.TransparentBlt(mDC, ui.Time[timeten]._left, ui.Time[timeten]._top,
			ui.Time[timeten]._right - ui.Time[timeten]._left + 20,
			ui.Time[timeten]._bottom - ui.Time[timeten]._top + 30, 0, 0,
			ui.Time[timeten]._width, ui.Time[timeten]._height, RGB(57, 81, 57));

		ui.Time[timeone]._right = ui.Time[timeone]._left + ui.Time[timeone]._width;
		ui.Time[timeone]._bottom = ui.Time[timeone]._top + ui.Time[timeone]._height;
		ui.Time[timeone]._img.TransparentBlt(mDC, ui.Time[timeone]._left + 28, ui.Time[timeone]._top,
			ui.Time[timeone]._right - ui.Time[timeone]._left + 20,
			ui.Time[timeone]._bottom - ui.Time[timeone]._top + 30, 0, 0,
			ui.Time[timeone]._width, ui.Time[timeone]._height, RGB(57, 81, 57));
	}
}

void GAMEMANAGER::printStart(HDC& mDC) {
	if (start <= 2) {
		ui.Start[start]._img.StretchBlt(mDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ui.Start[start]._width + 10, ui.Start[start]._height + 31);
	}
}

void GAMEMANAGER::printFight(HDC& mDC) {
	//Fight
	if (2 <= fight && fight <= 3) {
		ui.Fight._right = ui.Fight._left + ui.Fight._width;
		ui.Fight._bottom = ui.Fight._top + ui.Fight._height;
		ui.Fight._img.TransparentBlt(mDC, ui.Fight._left + 350, ui.Fight._top + 200, 
			ui.Fight._right - ui.Fight._left + 140, ui.Fight._bottom - ui.Fight._top + 70, 0, 0, 
			ui.Fight._width, ui.Fight._height, RGB(0, 0, 32));
	}
}

void GAMEMANAGER::printKO(HDC& mDC) {
	if (ko) {
		ui.KO._right = ui.KO._left + ui.KO._width;
		ui.KO._bottom = ui.KO._top + ui.KO._height;
		ui.KO._img.TransparentBlt(mDC, ui.KO._left + 365, ui.KO._top + 200, 
			ui.KO._right - ui.KO._left + 140, ui.KO._bottom - ui.KO._top + 70, 0, 0, 
			ui.KO._width, ui.KO._height, RGB(0, 0, 32));
		//PlaySound(TEXT("Announce_Ko.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void GAMEMANAGER::playbackgroundmusic() {
	// 배경음악 파일을 엽니다.
	MCIERROR mciError = mciSendString(TEXT("open \"character/sound/06-Hey_-_England-Stage_.wav\" type mpegvideo alias bgm"), NULL, 0, NULL);
	if (mciError != 0) {
		TCHAR errorText[128];
		mciGetErrorString(mciError, errorText, sizeof(errorText) / sizeof(TCHAR));
		std::cerr << "MCI open error: " << errorText << std::endl;
		return;
	}

	// 배경음악을 재생합니다.
	mciError = mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
	if (mciError != 0) {
		TCHAR errorText[128];
		mciGetErrorString(mciError, errorText, sizeof(errorText) / sizeof(TCHAR));
		std::cerr << "MCI play error: " << errorText << std::endl;
		mciSendString(TEXT("close bgm"), NULL, 0, NULL); // 에러 발생 시 파일 닫기
		return;
	}
}