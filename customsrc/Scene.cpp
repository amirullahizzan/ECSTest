#include "Scene.h"

Pos mousePos;
Scene* currentScene_p = nullptr;

void Scene::InitOnceFlag()
{
	if (isInit)
	{
		return;
	}
	else
	{
		Init();
		isInit = true;
	}
}

void Scene::Init()
{
}

void Scene::Update()
{

}

void Scene::Render()
{
}
bool Scene::IsMouseHitBox(const Pos& _boxPos1, const Pos& _boxPos2)
{
	if (HitboxBoxCircle(_boxPos1, _boxPos2, mousePos))
	{
		return true;
	}
	return false;
}
//#MAINMENUSCENE
MainMenuScene::~MainMenuScene()
{
}
MainMenuScene::MainMenuScene()
{
	SetFontSize(FONTSIZE_LARGE);
	for (int i = 0; i < buttonBox.size(); i++)
	{
	}
}

void MainMenuScene::Update()
{
	PlayerControl();
}
void MainMenuScene::Render()
{
	DisplayAnimatedTitle();
	DisplayAnimatedMenuText();
	printfDx("mouse %f , %f", mousePos.x_, mousePos.y_);
}

void MainMenuScene::PlayerControl()
{
	int mousePosX;
	int mousePosY;
	GetMousePoint(&mousePosX, &mousePosY);
	mousePos.x_ = static_cast<float>(mousePosX);
	mousePos.y_ = static_cast<float>(mousePosY);
	bool deleteFlag = false;

	if (IsMouseOn(MOUSE_INPUT_LEFT))
	{
		for (int i = 0; i < buttonBox.size(); i++)
		{
			if (IsMouseHitBox(buttonBox[i].GetPos1(), buttonBox[i].GetPos2()))
			{
				switch (i)
				{
				case 0:
					ResetTimedCharacter(textTickBuffer, charIndexBuffer);
					currentScene_p = new GameScene();
					deleteFlag = true;
					break;
				case 1:
					exit(0);
					break;
				}
			}
		}

		if (deleteFlag) delete this;
	}
}

void MainMenuScene::DisplayAnimatedTitle()
{
	int originalFontSize = GetFontSize();
	SetFontSize(FONTSIZE_TITLE);
	std::string gameTitle = "DeathGame";
	const int perCharTimer = 5;
	int textLength = GetTextSize(gameTitle);
	DrawString(WINDOW_W_HALF - textLength, WINDOW_H_HALF - 200,
		GetTimedCharacter(gameTitle, perCharTimer, textTickBuffer, charIndexBuffer).c_str(),
		YELLOW);

	SetFontSize(FONTSIZE_SMALL);
	std::string credit = "by アミルラ イザン";
	textLength = GetTextSize(credit);
	DrawString(WINDOW_W_HALF - textLength, WINDOW_H - 50,
		GetTimedCharacter(credit, perCharTimer, textTickBuffer, charIndexBuffer).c_str(),
		YELLOW);

	SetFontSize(originalFontSize);
}
void MainMenuScene::DisplayAnimatedMenuText()
{
	SetFontSize(FONTSIZE_LARGE);

	int fontSize = GetFontSize(); //get height
	const int buttonUIOffset = 140 + fontSize;

	for (int i = 0; i < buttonBox.size(); i++)
	{
		buttonBox[i] = { (float)WINDOW_W_HALF, (float)WINDOW_H_HALF + (buttonUIOffset * i), WINDOW_W,40,true };
		buttonBox[i].Render();

		const int perCharTimer = 50;
		//DrawCircleAA(buttonBox[i].pointPos_.x_, buttonBox[i].pointPos_.y_,64,64,RED,1,1);
		int textLength = GetTextSize((text[i])); //get width
		DrawStringF(buttonBox[i].pointPos_.x_ - textLength, buttonBox[i].pointPos_.y_ - fontSize * 0.5f,
			GetTimedCharacter(text[i], perCharTimer, textTickBuffer, charIndexBuffer).c_str(),
			BLACK);
	}
}

GameScene::GameScene()
{
	background_imageHandler = LoadGraph("data/pic/cardback.png");
}

void GameScene::Update()
{
	int mousePosX = static_cast<int>(mousePos.x_);
	int mousePosY = static_cast<int>(mousePos.y_);
	GetMousePoint(&mousePosX, &mousePosY);

	if (IsMouseOn(INPUT_MOUSE_LEFT))
	{
	}
}

void GameScene::Render()
{
	DrawBorderLine();
	//printfDx("CARDS :%d\n", playingCards_p.size());
	//printfDx("%d,%d\n", debugPos.x_, debugPos.y_);

}

void GameScene::DrawBorderLine()
{
	constexpr int LineWidth = 1200;
	DrawLineAA(UPPER_BORDER.x_, UPPER_BORDER.y_, UPPER_BORDER.x_ + LineWidth, UPPER_BORDER.y_, WHITE, 3);
}



//#ENDGAMESCENE
void EndGameScene::Update()
{
}

void EndGameScene::Render()
{

}



