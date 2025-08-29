#include "FadeBox.h"
extern Time gameTime;
void FadeBox::Render()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(blendparam_));
	DrawBoxAA(pos_.x_, pos_.y_, pos2_.x_, pos2_.y_, BLACK, 1, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 1);
}

void FadeBox::SetFadeOut()
{
	if (blendparam_ <= DX_NO_ALPHA)
	{
		delete this;
	}
	else if(blendparam_ > DX_NO_ALPHA)
	{
		blendparam_ -= gameTime.deltaTime;
	}
}

void FadeBox::SetFadeIn()
{
	if (blendparam_ <= DX_MAX_ALPHA)
	{
		blendparam_+=gameTime.deltaTime;
	}
}

