#include "DxLib.h"
#include <stdlib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	const int WIDTH = 960, HEIGHT = 640;
	const int WHITE = GetColor(255, 255, 255);

	SetWindowText("ヒットチェック");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	int x1 = 0, y1 = 0, w1 = 120, h1 = 80;
	int x2 = WIDTH / 2, y2 = HEIGHT / 2, w2 = 160, h2 = 240;

	while (1)
	{
		ClearDrawScreen();

		GetMousePoint(&x1, &y1);
		int col1 = GetColor(255, 0, 0);
		int col2 = GetColor(0, 0, 255);
		int dx = abs((x1 - x2));
		int dy = abs((y1 - y2));
		if (dx <= (w1 + w2) / 2 && dy <= (h1 + h2) / 2)
		{
			col1 = GetColor(255, 255, 0);
			col2 = GetColor(0, 255, 255);
		}
		DrawBox(x1 - w1 / 2, y1 - h1 / 2, x1 + w1 / 2, y1 + h1 / 2, col1, TRUE);
		DrawBox(x2 - w2 / 2, y2 - h2 / 2, x2 + w2 / 2, y2 + h2 / 2, col2, TRUE);

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1)break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
	}

	DxLib_End();
	return 0;
}