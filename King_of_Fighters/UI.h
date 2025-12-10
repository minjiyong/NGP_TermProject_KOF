#pragma once
#include "IMAGE.h"

class UI {
public:
	IMAGE HP[3];
	IMAGE MAP1;
	IMAGE MAP2;
	IMAGE MAP3;
	IMAGE ChinName;
	IMAGE KapName;
	IMAGE ChinProfile;
	IMAGE KapProfile;
	IMAGE Time[10];
	IMAGE Start[2];
	IMAGE Fight;
	IMAGE KO;

	UI();
	~UI();

	void SetUI();
};