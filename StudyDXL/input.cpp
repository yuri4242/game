#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	
	const int WIDTH = 960, HEIGHT = 640;
	const int WHITE = GetColor(255, 255, 255);

	SetWindowText("DXライブラリの使い方");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	int timer = 0;

	while (1) {
	
		ClearDrawScreen();
		timer++;
		DrawFormatString(0, 0, WHITE, "%d", timer);//"%d"などの書式指定子を含む場合はDrawFormatString。

		
		if (CheckHitKey(KEY_INPUT_UP))    DrawString(0, 20, "上キー", WHITE);//書式指定子を含まない場合はDrawString
		if (CheckHitKey(KEY_INPUT_DOWN))  DrawString(0, 20, "下キー", WHITE);
		if (CheckHitKey(KEY_INPUT_LEFT))  DrawString(0, 20, "左キー", WHITE);
		if (CheckHitKey(KEY_INPUT_RIGHT)) DrawString(0, 20, "右キー", WHITE);

		
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);//GetMousePointにはポインタを渡す。
		DrawFormatString(400, 0, WHITE, "(%d, %d)", mouseX, mouseY);
		if (GetMouseInput() & MOUSE_INPUT_LEFT)  DrawString(400, 20, "左ボタン", WHITE);
		if (GetMouseInput() & MOUSE_INPUT_RIGHT) DrawString(400, 20, "右ボタン", WHITE);

		ScreenFlip(); //裏画面に描いたものを表画面に反映させる
		WaitTimer(33);//指定のミリ秒間、処理を一時停止させる。1000ms/33ms=30times/min
		if (ProcessMessage() == -1) break;//Windowsシステムからの情報を受けるDXライブラリの関数。
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;
}