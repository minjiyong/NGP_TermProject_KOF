#include "UI.h"

UI::UI() {};

UI::~UI() {};

void UI::SetUI() {
	HP[0].SetImage(L"image/HPbar1.png", 93, 20, 0, 0);
	HP[1].SetImage(L"image/HPbar2.png", 93, 20, 0, 0);
	HP[2].SetImage(L"image/HPbar3.png", 93, 20, 0, 0);
	MAP1.SetImage(L"image/Background 1-1.png", 0, 0, 0, 0);
	MAP2.SetImage(L"image/Background 1-2.png", 0, 0, 0, 0);
	MAP3.SetImage(L"image/Background 1-3.png", 0, 0, 0, 0);
	ChinName.SetImage(L"image/Chin_name.png", 173, 69, 0, 0);
	KapName.SetImage(L"image/Kap_name.png", 538, 69, 0, 0);
	ChinProfile.SetImage(L"image/Chin_profile.png", 126, 40, 0, 0);
	KapProfile.SetImage(L"image/Kap_profile.png", 711, 40, 0, 0);
	Time[0].SetImage(L"image/Time0.png", 414, 37, 8, 12);
	Time[1].SetImage(L"image/Time1.png", 414, 37, 8, 12);
	Time[2].SetImage(L"image/Time2.png", 414, 37, 8, 12);
	Time[3].SetImage(L"image/Time3.png", 414, 37, 8, 12);
	Time[4].SetImage(L"image/Time4.png", 414, 37, 8, 12);
	Time[5].SetImage(L"image/Time5.png", 414, 37, 8, 12);
	Time[6].SetImage(L"image/Time6.png", 414, 37, 8, 12);
	Time[7].SetImage(L"image/Time7.png", 414, 37, 8, 12);
	Time[8].SetImage(L"image/Time8.png", 414, 37, 8, 12);
	Time[9].SetImage(L"image/Time9.png", 414, 37, 8, 12);
	Start[0].SetImage(L"image/Start1.png", 0, 0, 0, 0);
	Start[1].SetImage(L"image/Start2.png", 0, 0, 0, 0);
	Fight.SetImage(L"image/Fight.png", 0, 0, 48, 15);
	KO.SetImage(L"image/KO.png", 0, 0, 15, 8);
	std::cout << "UI Set Complete" << std::endl;
}