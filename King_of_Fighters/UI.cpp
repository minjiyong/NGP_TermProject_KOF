#include "UI.h"

UI::UI() {};

UI::~UI() {};

void UI::SetUI() {
	HP.SetImage(L"HPbar.png", 93, 20, 0, 0);
	MAP1.SetImage(L"Background 1-1.png", 0, 0, 0, 0);
	MAP2.SetImage(L"Background 1-2.png", 0, 0, 0, 0);
	MAP3.SetImage(L"Background 1-3.png", 0, 0, 0, 0);
	ChinName.SetImage(L"Chin_name.png", 173, 69, 0, 0);
	KapName.SetImage(L"Kap_name.png", 538, 69, 0, 0);
	ChinProfile.SetImage(L"Kap_profile.png", 126, 40, 0, 0);
	KapProfile.SetImage(L"Chin_profile.png", 711, 40, 0, 0);
	Time[0].SetImage(L"Time0.png", 414, 37, 0, 0);
	Time[1].SetImage(L"Time1.png", 414, 37, 0, 0);
	Time[2].SetImage(L"Time2.png", 414, 37, 0, 0);
	Time[3].SetImage(L"Time3.png", 414, 37, 0, 0);
	Time[4].SetImage(L"Time4.png", 414, 37, 0, 0);
	Time[5].SetImage(L"Time5.png", 414, 37, 0, 0);
	Time[6].SetImage(L"Time6.png", 414, 37, 0, 0);
	Time[7].SetImage(L"Time7.png", 414, 37, 0, 0);
	Time[8].SetImage(L"Time8.png", 414, 37, 0, 0);
	Time[9].SetImage(L"Time9.png", 414, 37, 0, 0);
	Start[0].SetImage(L"Start1.png", 0, 0, 0, 0);
	Start[1].SetImage(L"Start2.png", 0, 0, 0, 0);
	Fight.SetImage(L"Fight.png", 0, 0, 0, 0);
	KO.SetImage(L"KO.png", 0, 0, 0, 0);
}