#include "DxLib.h"
#include <math.h>

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

	int x1 = 0, y1 = 0, r1 = 80;
	int x2 = WIDTH / 2, y2 = HEIGHT / 2, r2 = 120;

	while (1)
	{
		ClearDrawScreen();

		GetMousePoint(&x1, &y1);
		int col1 = GetColor(255, 0, 0);
		int col2 = GetColor(0, 0, 255);
		int d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) + (y1 - y2));
		DrawFormatString(0, 0, WHITE, "中心間距離　%d", d);
		if (d <= r1 + r2)
		{
			col1 = GetColor(255, 255, 0);
			col2 = GetColor(0, 255, 255);
		}
		DrawCircle(x1, y1, r1, col1, TRUE);
		DrawCircle(x2, y2, r2, col2, TRUE);

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1)break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
	}

	DxLib_End();
	return 0;
}