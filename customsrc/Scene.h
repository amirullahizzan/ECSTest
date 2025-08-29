#pragma once
#pragma once
#include "../src/WinMain.h"
//#include "../customlib/Pos.h"
#include "../customlib/Primitive.h"
#include "../customlib/HitBox.h"
#include "../customlib/TextEffect.h"
#include <random>

struct Scene
{
	bool isInit = false;
	virtual void Init();
	virtual void Update();
	virtual void Render();
protected:
	void InitOnceFlag();
	bool IsMouseHitBox(const Pos& _boxPos1, const Pos& _boxPos2);
};

struct MainMenuScene : public Scene
{
	MainMenuScene();
	~MainMenuScene();

	void Update() override;
	void Render() override;


private:
	std::array<Box, 2> buttonBox = {};
	std::string text[2] = { "Start" , "Exit" };

	int textTickBuffer = 0;
	int charIndexBuffer = 0;
	void PlayerControl();
	void DisplayAnimatedTitle();
	void DisplayAnimatedMenuText();
	//void CarrouselObject();
};

struct GameScene : public Scene
{
	GameScene();
	void Update() override;
	void Render() override;

private:

	const Pos UPPER_BORDER = { 50,200 };
	const Pos BORDER_OFFSET = { 50,100 };

	int background_imageHandler = -1;

	void DrawBorderLine();
	
};

struct EndGameScene : public Scene
{
	void Update() override;
	void Render() override;
};

