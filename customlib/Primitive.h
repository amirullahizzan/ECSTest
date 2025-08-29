#include "../src/WinMain.h"
#include "Pos.h"

struct Box
{
	Pos pointPos_ = { WINDOW_W_HALF,WINDOW_H_HALF };

	bool isDrawn = false;
	bool isFaceUp = false;
	//int hitboxRadius = 42;

	Box();
	Box(float _x, float _y, float _sizeX, float _sizeY, bool _hasShadow = false);

	Pos pos_;
	Pos pos2_;
	Pos size_;

	void Update();
	void Render();

	Pos GetPos1() const;
	Pos GetPos2() const;
	Pos GetPointPos() const;

	void SetPointPos(Pos& pointpos_);

private:
	bool hasShadow_ = false;

	void RenderBox(Pos& _pos, Pos& _pos2);
	void RenderShadow(Pos& _pos, Pos& _pos2);
};
