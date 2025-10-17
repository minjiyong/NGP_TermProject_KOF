#include <windows.h>
#include <iostream>
#include <atlImage.h>
#include "Chin_bigkick.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

Chin_bigkick::Chin_bigkick() {};

Chin_bigkick::~Chin_bigkick() {};

void Chin_bigkick::bigkick_img_load() {
	bigkick_ani[0].img.Load(L"Chin Gentsai_94.png");
	bigkick_ani[1].img.Load(L"Chin Gentsai_95.png");
	bigkick_ani[2].img.Load(L"Chin Gentsai_96.png");
	bigkick_ani[3].img.Load(L"Chin Gentsai_97.png");
	bigkick_ani[4].img.Load(L"Chin Gentsai_98.png");
	bigkick_ani[5].img.Load(L"Chin Gentsai_98.png");
	bigkick_ani[6].img.Load(L"Chin Gentsai_97.png");
	bigkick_ani[7].img.Load(L"Chin Gentsai_96.png");
	std::cout << "강발 이미지 로드됨" << std::endl;
}

void Chin_bigkick::goto_next_img()
{
	ani_index++;
}
