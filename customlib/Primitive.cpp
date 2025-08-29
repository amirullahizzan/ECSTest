#include "Primitive.h"

Box::Box()
{
	hasShadow_ = false;
	Update();
}

Box::Box(float _x, float _y, float _sizeX, float _sizeY, bool _hasShadow)
{
	pointPos_.x_ = _x;
	pointPos_.y_ = _y;
	size_.x_ = _sizeX;
	size_.y_ = _sizeY;
	hasShadow_ = _hasShadow;
	Update();
}

void Box::Update()
{
	pos_ = { (pointPos_.x_ - size_.x_), (pointPos_.y_ - size_.y_) };
	pos2_ = { (pointPos_.x_ + size_.x_), (pointPos_.y_ + size_.y_) };
}

void Box::Render()
{
	if (hasShadow_)
	{
		RenderShadow(pos_, pos2_);
	}
	RenderBox(pos_, pos2_); 
}

Pos Box::GetPos1() const
{
	return pos_;
}
Pos Box::GetPos2() const
{
	return pos2_;
}

Pos Box::GetPointPos() const
{
	return pointPos_;
}

void Box::SetPointPos(Pos& _pointPos)
{
	pointPos_ = _pointPos;
}

void Box::RenderBox(Pos& _pos, Pos& _pos2)
{
	DrawBoxAA(_pos.x_, _pos.y_, _pos2.x_, _pos2.y_, WHITE, 1);
}


void Box::RenderShadow(Pos& _pos, Pos& _pos2)
{
	const float shadowOffset = 5.0f;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBoxAA(_pos.x_- shadowOffset, _pos.y_, _pos2.x_, _pos2.y_+ shadowOffset, BLACK, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 120);
}
