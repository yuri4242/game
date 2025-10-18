#include "DxLib.h"
#include "ShootingGame.h"
#include <stdlib.h>


const int WIDTH = 1200, HEIGHT = 720;
const int FPS = 60;
const int IMG_ENEMY_MAX = 5;
const int BULLET_MAX = 100;
const int ENEMY_MAX = 100;
const int STAGE_DISTANCE = FPS * 60;
const int PLAYER_SHIELD_MAX = 8;
const int EFFECT_MAX = 100;
const int ITEM_TYPE = 3;
const int WEAPON_LV_MAX = 10;
const int PLAYER_SPEED_MAX = 20;
enum { ENE_BULLET, ENE_ZAKO1, ENE_ZAKO2, ENE_ZAKO3, ENE_BOSS };
enum { EFF_EXPLODE, EFF_RECOVER };



int imgGalaxy, imgFloor, imgWallL, imgWallR;
int imgFighter, imgBullet;
int imgEnemy[IMG_ENEMY_MAX];
int imgExplosion;
int imgItem;
int bgm, jinOver, jinClear, seExpl, seItem, seShot;
int distance = 0;
int bossIdx = 0;
int stage = 1;
int score = 0;
int hisco = 10000;
int noDamage = 0;
int weaponLv = 1;

struct OBJECT player;
struct OBJECT bullet[BULLET_MAX];
struct OBJECT enemy[ENEMY_MAX];
struct OBJECT effect[EFFECT_MAX];
struct OBJECT item;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowText("ShootingGame");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	initGame();
	initVariable();
	distance = STAGE_DISTANCE;

	while (1)
	{
		ClearDrawScreen();


		scrollBG(1);
		if (distance > 0) distance--;
		DrawFormatString(0, 0, 0xffff00, "SCORE %d HI-SCO %d", score, hisco);
		if (distance % 60 == 1)
		{
			int x = 100 + rand() % (WIDTH - 200);
			int y = 50;
			int e = 1 + rand() % 2;
			if (e == ENE_ZAKO1) setEnemy(x, y, 0, 3, ENE_ZAKO1, imgEnemy[ENE_ZAKO1], 1);
			if (e == ENE_ZAKO2) {
				int vx = 0;
				if (player.x < x - 50)vx = -3;
				if (player.x > x + 50)vx = 3;
				setEnemy(x, -100, vx, 5, ENE_ZAKO2, imgEnemy[ENE_ZAKO2], 3);
			}
		}
		if (distance % 120 == 1)
		{
			int x = 100 + rand() % (WIDTH - 200);
			setEnemy(x, -100, 0, 40 + rand() % 20, ENE_ZAKO3, imgEnemy[ENE_ZAKO3], 5);
		}
		if (distance == 1) bossIdx = setEnemy(WIDTH / 2, -120, 0, 1, ENE_BOSS, imgEnemy[ENE_BOSS], 200);
		moveEnemy();
		movePlayer();
		moveBullet();
		moveItem();
		drawEffect();
		stageMap();
		drawParameter();

		ScreenFlip();
		WaitTimer(1000 / FPS);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;
}



void initGame(void)
{

	imgGalaxy = LoadGraph("image/bg0.png");
	imgFloor = LoadGraph("image/bg1.png");
	imgWallL = LoadGraph("image/bg2.png");
	imgWallR = LoadGraph("image/bg3.png");

	imgFighter = LoadGraph("image/fighter.png");
	imgBullet = LoadGraph("image/bullet.png");

	for (int i = 0; i < IMG_ENEMY_MAX; i++){
		char file[] = "image/enemy*.png";
		file[11] = (char)('0' + i);
		imgEnemy[i] = LoadGraph(file);
	}

	imgExplosion = LoadGraph("image/explosion.png");
	imgItem = LoadGraph("image/item.png");


	bgm = LoadSoundMem("sound/bgm.mp3");
	jinOver = LoadSoundMem("sound/gameover.mp3");
	jinClear = LoadSoundMem("sound/stageclear.mp3");
	seExpl = LoadSoundMem("sound/explosion.mp3");
	seItem = LoadSoundMem("sound/item.mp3");
	seShot = LoadSoundMem("sound/shot.mp3");
	ChangeVolumeSoundMem(128, bgm);
	ChangeVolumeSoundMem(128, jinOver);
	ChangeVolumeSoundMem(128, jinClear);
}


void scrollBG(int spd)
{
	static int galaxyY, floorY, wallY;
	galaxyY = (galaxyY + spd) % HEIGHT;
	DrawGraph(0, galaxyY - HEIGHT, imgGalaxy, FALSE);
	DrawGraph(0, galaxyY, imgGalaxy, FALSE);
	floorY = (floorY + spd * 2) % 120;
	for (int i = -1; i < 6; i++) DrawGraph(240, floorY + i * 120, imgFloor, TRUE);
	wallY = (wallY + spd * 4) % 240;
	DrawGraph(0, wallY - 240, imgWallL, TRUE);
	DrawGraph(WIDTH - 300, wallY - 240, imgWallR, TRUE);
}



void initVariable(void)
{
	player.x = WIDTH / 2;
	player.y = HEIGHT / 2;
	player.vx = 5;
	player.vy = 5;
	player.shield = PLAYER_SHIELD_MAX;
	GetGraphSize(imgFighter, &player.wid, &player.hei);
}


void drawImage(int img, int x, int y)
{
	int w, h;
	GetGraphSize(img, &w, &h);
	DrawGraph(x - w / 2, y - h / 2, img, TRUE);
}


void movePlayer(void)
{
	static char oldSpcKey;
	static int  countSpcKey;
	if (CheckHitKey(KEY_INPUT_UP)) {
		player.y -= player.vy;
		if (player.y < 30) player.y = 30;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		player.y += player.vy;
		if (player.y > HEIGHT - 30) player.y = HEIGHT - 30;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		player.x -= player.vx;
		if (player.x < 30) player.x = 30;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		player.x += player.vx;
		if (player.x > WIDTH - 30) player.x = WIDTH - 30;
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (oldSpcKey == 0) setBullet();
		else if (countSpcKey % 20 == 0) setBullet();
		countSpcKey++;
	}
	oldSpcKey = CheckHitKey(KEY_INPUT_SPACE);
	drawImage(imgFighter, player.x, player.y);
	if (noDamage > 0) noDamage--;
	if (noDamage % 4 < 2) drawImage(imgFighter, player.x, player.y);
}

void setBullet(void)
{
	for (int n = 0; n < weaponLv; n++) {
		int x = player.x - (weaponLv - 1) * 5 + n * 10;
		int y = player.y - 20;
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bullet[i].state == 0) {
				bullet[i].x = player.x;
				bullet[i].y = player.y - 20;
				bullet[i].vx = 0;
				bullet[i].vy = -40;
				bullet[i].state = 1;
				break;
			}
		}
	}
	PlaySoundMem(seShot, DX_PLAYTYPE_BACK);
}


void moveBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullet[i].state == 0) continue;
		bullet[i].x += bullet[i].vx;
		bullet[i].y += bullet[i].vy;
		drawImage(imgBullet, bullet[i].x, bullet[i].y);
		if (bullet[i].y < -100) bullet[i].state = 0;
	}
}


int setEnemy(int x, int y, int vx, int vy, int ptn, int img, int sld)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].state == 0) {
			enemy[i].x = x;
			enemy[i].y = y;
			enemy[i].vx = vx;
			enemy[i].vy = vy;
			enemy[i].state = 1;
			enemy[i].pattern = ptn;
			enemy[i].image = img;
			enemy[i].shield = sld * stage;
			GetGraphSize(img, &enemy[i].wid, &enemy[i].hei);
			return i;
		}
	}
	return -1;
}


void moveEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].state == 0) continue;
		if (enemy[i].pattern == ENE_ZAKO3)
		{
			if (enemy[i].vy > 1)
			{
				enemy[i].vy *= 0.9;
			}
			else if (enemy[i].vy > 0)
			{
				setEnemy(enemy[i].x, enemy[i].y, 0, 6, ENE_BULLET, imgEnemy[ENE_BULLET], 0);
				enemy[i].vx = 8;
				enemy[i].vy = -4;
			}
		}
		if (enemy[i].pattern == ENE_BOSS)
		{
			if (enemy[i].y > HEIGHT - 120) enemy[i].vy = -2;
			if (enemy[i].y < 120)
			{
				if (enemy[i].vy < 0)
				{
					for(int bx = -2; bx <= 2; bx++)
						for (int by = 0; by <= 3; by++)
						{
							if (bx == 0 && by == 0) continue;
							setEnemy(enemy[i].x, enemy[i].y, bx * 2, by * 3, ENE_BULLET, imgEnemy[ENE_BULLET], 0);
						}
				}
				enemy[i].vy = 2;
			}
		}
		enemy[i].x += enemy[i].vx;
		enemy[i].y += enemy[i].vy;
		drawImage(enemy[i].image, enemy[i].x, enemy[i].y);

		if (enemy[i].x < -200 || WIDTH + 200 < enemy[i].x || enemy[i].y < -200 || HEIGHT + 200 < enemy[i].y) enemy[i].state = 0;
		if (enemy[i].shield > 0)
		{
			for (int j = 0; j < BULLET_MAX; j++) {
				if (bullet[j].state == 0) continue;
				int dx = abs((int)enemy[i].x - bullet[j].x);
				int dy = abs((int)enemy[i].y - bullet[j].y);
				if (dx < enemy[i].wid / 2 && dy < enemy[i].hei / 2)
				{
					bullet[j].state = 0;
					damageEnemy(i, 1);
				}
			}
		}
		if (noDamage == 0)
		{
			int dx = abs(enemy[i].x - player.x);
			int dy = abs(enemy[i].y - player.y);
			if (dx < enemy[i].wid / 2 + player.wid / 2 && dy < enemy[i].hei / 2 + player.hei / 2)
			{
				if (player.shield > 0) player.shield--;
				noDamage = FPS;
				damageEnemy(i, 1);
			}
		}
	}
}

void stageMap(void)
{
	int mx = WIDTH - 30, my = 60;
	int wi = 20, he = HEIGHT - 120;
	int pos = (HEIGHT - 140) * distance / STAGE_DISTANCE;
	SetDrawBlendMode(DX_BLENDMODE_SUB, 128);
	DrawBox(mx, my, mx + wi, my + he, 0xffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(mx - 1, my - 1, mx + wi + 1, my + he + 1, 0xffffff, FALSE);
	DrawBox(mx, my + pos, mx + wi, my + pos + 20, 0x0080ff, TRUE);
}



void damageEnemy(int n, int dmg)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
	DrawCircle(enemy[n].x, enemy[n].y, (enemy[n].wid + enemy[n].hei) / 4, 0xff0000, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	score += 100;
	if (score > hisco) hisco = score;
	enemy[n].shield -= dmg;
	if (enemy[n].shield <= 0)
	{
		enemy[n].state = 0;
		setEffect(enemy[n].x, enemy[n].y, EFF_EXPLODE);
	}
}

void drawText(int x, int y, const char* txt, int val, int col, int siz)
{
	SetFontSize(siz);
	DrawFormatString(x + 1, y + 1, 0x000000, txt, val);
	DrawFormatString(x, y, col, txt, val);
}


void drawParameter(void)
{
	int x = 10, y = HEIGHT - 30;
	DrawBox(x, y, x + PLAYER_SHIELD_MAX * 30, y + 20, 0x000000, TRUE);
	for (int i = 0; i < player.shield; i++)
	{
		int r = 128 * (PLAYER_SHIELD_MAX - i) / PLAYER_SHIELD_MAX;
		int g = 255 * i / PLAYER_SHIELD_MAX;
		int b = 160 + 96 * i / PLAYER_SHIELD_MAX;
		DrawBox(x + 2 + i * 30, y + 2, x + 28 + i * 30, y + 18, GetColor(r, g, b), TRUE);
	}
	drawText(x, y - 25, "SHIELD Lv %02d", player.shield, 0xffffff, 20);
	drawText(x, y - 50, "WEAPON Lv %02d", weaponLv, 0xffffff, 20);
	drawText(x, y - 75, "SPEED %02d", player.vx, 0xffffff, 20);
}



void setEffect(int x, int y, int ptn)
{
	static int eff_num;
	effect[eff_num].x = x;
	effect[eff_num].y = y;
	effect[eff_num].state = 1;
	effect[eff_num].pattern = ptn;
	effect[eff_num].timer = 0;
	eff_num = (eff_num + 1) % EFFECT_MAX;
	if (ptn == EFF_EXPLODE) PlaySoundMem(seExpl, DX_PLAYTYPE_BACK);
}


void drawEffect(void)
{
	int ix;
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (effect[i].state == 0) continue;
		switch (effect[i].pattern)
		{
		case EFF_EXPLODE:
			ix = effect[i].timer * 128;
			DrawRectGraph(effect[i].x - 64, effect[i].y - 64, ix, 0, 128, 128, imgExplosion, TRUE, FALSE);
			effect[i].timer++;
			if (effect[i].timer == 7) effect[i].state = 0;
			break;

		case EFF_RECOVER:
			if (effect[i].timer < 30)
				SetDrawBlendMode(DX_BLENDMODE_ADD, effect[i].timer * 8);
			else
				SetDrawBlendMode(DX_BLENDMODE_ADD, (60 - effect[i].timer) * 8);
			for (int i = 3; i < 8; i++) DrawCircle(player.x, player.y, (player.wid + player.hei) / i, 0x2040c0, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			effect[i].timer++;
			if (effect[i].timer == 60) effect[i].state == 0;
			break;
		}
	}
}



void setItem(void) 
{
	item.x = (WIDTH / 4) * (1 + rand() % 3);
	item.y = -16;
	item.vx = 15;
	item.vy = 1;
	item.state = 1; 
	item.timer = 0;
}


void moveItem(void)
{
	if (item.state == 0) return;
	item.x += item.vx;
	item.y += item.vy;
	if (item.timer % 60 < 30)
		item.vx -= 1;
	else
		item.vx += 1;
	if (item.y > HEIGHT + 16) item.state = 0;
	item.pattern = (item.timer / 120) % ITEM_TYPE;
	item.timer++;
	DrawRectGraph(item.x - 20, item.y - 16, item.pattern * 40, 0, 40, 32, imgItem, TRUE, FALSE);
	//if (scene == OVER)return;
	int dis = (item.x - player.x) * (item.x - player.x) + (item.y - player.y) * (item.y - player.y);
	if (dis < 60 * 60)
	{
		item.state = 0;
		if (item.pattern == 0)
		{
			if (player.vx < PLAYER_SPEED_MAX)
			{
				player.vx += 3;
				player.vy += 3;
			}
		}
		if (item.pattern == 1)
		{
			if (player.shield < PLAYER_SHIELD_MAX) player.shield++;
			setEffect(player.x, player.y, EFF_RECOVER);
		}
		if (item.pattern == 2)
		{
			if (weaponLv < WEAPON_LV_MAX) weaponLv++;
		}
		PlaySoundMem(seItem, DX_PLAYTYPE_BACK);
	}
}