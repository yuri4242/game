#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


	const int WIDTH = 1060, HEIGHT = 640;
	const int WHITE = GetColor(255, 255, 255);

	SetWindowText("DXライブラリの使い方");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	int timer = 0;

	while(1)
	{
		ClearDrawScreen();
		timer++;
		DrawFormatString(0, 0, WHITE, "%d", timer);

		DrawLine(0, 0, WIDTH, HEIGHT, GetColor(255, 0, 0));
		DrawBox(0, HEIGHT - 400, 200, HEIGHT - 100, GetColor(0, 255, 0), TRUE);
		DrawBox(WIDTH - 200, 100, WIDTH - 100, 200, GetColor(0, 0, 255), TRUE);
		DrawCircle(400, 200, 100, GetColor(0, 255, 255), TRUE);
		DrawOval(400, 400, 200, 100, GetColor(255, 0, 255), FALSE);
		DrawTriangle(600, 0, 500, 300, 700, 300, GetColor(255, 192, 0), TRUE);
		DrawPixel(400, 200, GetColor(0, 0, 0));

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1)break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
	}

	DxLib_End();
	return 0;
}