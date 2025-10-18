#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	const int WIDTH = 960, HEIGHT = 640;
	const int WHITE = GetColor(255, 255, 255);
	const int RED = GetColor(255, 0, 0);

	SetWindowText("画面遷移");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	int timer = 0;
	enum { TITLE, PLAY, MENU, CLEAR, OVER };
	int scene = TITLE;

	while (1)
	{
		ClearDrawScreen();
		timer++;
		SetFontSize(16);
		DrawFormatString(0, 0, WHITE, "%d", timer);

		switch (scene)
		{
		case TITLE:
			SetFontSize(50);
			DrawString(100, 50, "タイトル画面", WHITE);
			SetFontSize(20);
			DrawString(100, 200, "Sキーを押すとゲーム開始", WHITE);
			if (CheckHitKey(KEY_INPUT_S) == 1) scene = PLAY;
			break;

		case PLAY:
			SetFontSize(50);
			DrawString(100, 50, "ゲーム画面", WHITE);
			SetFontSize(20);
			DrawString(100, 200, "Mキーでメニュー画面へ", WHITE);
			SetFontSize(20);
			DrawString(100, 300, "Oキーでゲームオーバー", WHITE);
			if (CheckHitKey(KEY_INPUT_M) == 1) scene = MENU;
			if (CheckHitKey(KEY_INPUT_O) == 1)
			{
				scene = OVER;
				timer = 0;
			}
			break;

		case MENU:
			SetFontSize(50);
			DrawString(100, 50, "メニュー画面", WHITE);
			SetFontSize(20);
			DrawString(100, 200, "Rキーでゲームに戻る", WHITE);
			if (CheckHitKey(KEY_INPUT_R) == 1) scene = PLAY;
			break;

		case CLEAR:

			break;

		case OVER:
			SetFontSize(50);
			DrawString(100, 50, "ゲームオーバー", WHITE);
			if (timer > 30 * 5) scene = TITLE;
			break;
		}

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}

	DxLib_End();
	return 0;
}