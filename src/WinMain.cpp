#include "WinMain.h"

#include <entt/entt.hpp>

#define DEBUG

void CreateConsole()
{
	// Attach a new console window
	AllocConsole();

	// Redirect standard streams
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONIN$", "r", stdin);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CreateConsole();

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetWindowSize(WINDOW_W, WINDOW_H);
	SetGraphMode(WINDOW_W, WINDOW_H, 32);
	SetBackgroundColor(200, 200, 200);
	SetMainWindowText("DeathGame");
	if (DxLib_Init() == -1) { return -1; }


	SetDrawScreen(DX_SCREEN_BACK);

	SRand((int)time(NULL));

	KeyInputInit();
	PadInputInit();
	MouseInputInit();

	entt::registry registry;

	GameInit(registry);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		KeyInputUpdate();
		PadInputUpdate();
		MouseInputUpdate();
		GameUpdate(registry);

		ClearDrawScreen();
#ifdef DEBUG
		clsDx();
#endif

		GameDraw(registry);
		ScreenFlip();
	}



	GameExit();

	DxLib_End();

	return 0;
}