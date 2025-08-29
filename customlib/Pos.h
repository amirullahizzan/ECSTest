#pragma once

struct Pos
{
	Pos()
	{
		x_ = 0;
		y_ = 0;
	}

	Pos(float _x, float _y)
	{
		x_ = _x;
		y_ = _y;
	}
	float x_, y_;
};