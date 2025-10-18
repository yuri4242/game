#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	const int WIDTH = 960, HEIGHT = 640;
	const int WHITE = GetColor(255, 255, 255);

	SetWindowText("DXライブラリの使い方");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	int timer = 0;
	int imgBG = LoadGraph("image/bg.png");
	int imgDog[4] = {
		LoadGraph("image/dog0.png"),
		LoadGraph("image/dog1.png"),
		LoadGraph("image/dog2.png"),
		LoadGraph("image/dog3.png"),
	};
	int dogX = 0, dogY = 400;

	while (1)
	{
		ClearDrawScreen();

		DrawGraph(0, 0, imgBG, FALSE);
		dogX = dogX + 10;
		if (dogX > WIDTH) dogX = -200;
		DrawGraph(dogX, dogY, imgDog[(timer / 5) % 4], TRUE);

		timer++;
		DrawFormatString(0, 0, WHITE, "%d", timer);

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1)break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
	}

	DxLib_End();
	return 0;

}