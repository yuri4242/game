#include "Dxlib.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (DxLib_Init() == -1)return -1;
	DrawCircle(320, 240, 100, 0x0000ff);
	WaitKey();
	DxLib_End();
	return 0;
}