#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLind, int nCmdShow)
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
	int bgm = LoadSoundMem("sound/battle.mp3");
	int se = LoadSoundMem("sound/recover.mp3");
	ChangeVolumeSoundMem(128, bgm);
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	while (1)
	{
		ClearDrawScreen();
		timer++;
		DrawFormatString(0, 0, WHITE, "%d", timer);


		DrawString(0, 20, "Sキーを押すとBGMを停止します。", WHITE);
		DrawString(0, 40, "スペースキーを押すと効果音を出力します。", WHITE);
		if (CheckHitKey(KEY_INPUT_S)) StopSoundMem(bgm);
		if (CheckHitKey(KEY_INPUT_SPACE)) StopSoundMem(se, DX_PLAYTYPE_BACK);

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1)break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
	}

	DxLib_End();
	return 0;
}