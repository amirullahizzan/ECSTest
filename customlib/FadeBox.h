#include "../src/WinMain.h"
#include "Pos.h"
#include "Time.h"

struct FadeBox
{
	Pos pos_ = { 0,0 };
	Pos pos2_ = { WINDOW_W,WINDOW_H };
	float blendparam_ = 0;

	void SetFadeOut();
	void SetFadeIn();
	void Render();
};