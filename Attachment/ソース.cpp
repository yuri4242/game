#include "DxLib.h"
#include <math.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // �萔�̒�`
    const int WIDTH = 960, HEIGHT = 640; // �E�B���h�E�̕��ƍ����̃s�N�Z����
    const int GRAY = GetColor(128, 128, 128); // �悭�g���F���`

    SetWindowText("�O�p�֐���p�����G�t�F�N�g"); // �E�B���h�E�̃^�C�g��
    SetGraphMode(WIDTH, HEIGHT, 32); // �E�B���h�E�̑傫���ƃJ���[�r�b�g���̎w��
    ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ŋN��
    if (DxLib_Init() == -1) return -1; // ���C�u���������� �G���[���N������I��
    SetBackgroundColor(0, 0, 0); // �w�i�F�̎w��
    SetDrawScreen(DX_SCREEN_BACK); // �`��ʂ𗠉�ʂɂ���

    const int RADIUS = 300; // �~�^���̔��a
    int degree = 0; // �p�x�𐔂���ϐ�

    while (1) // ���C�����[�v
    {
        ClearDrawScreen(); // ��ʂ�N���A����

        // ���Ɖ~����`��
        DrawLine(WIDTH / 2, 0, WIDTH / 2, HEIGHT, GRAY); // y��
        DrawLine(0, HEIGHT / 2, WIDTH, HEIGHT / 2, GRAY); // x��
        DrawCircle(WIDTH / 2, HEIGHT / 2, RADIUS, GRAY, FALSE); // ���aRADIUS�̉~

        degree++; // �p�x��1�x�����₵�Ă���
        double radian = 3.141592 * degree / 180; // ���W�A���ɕϊ�����
        DrawFormatString(0, 0, GRAY, "degree = %d", degree); // �x�̒l��\��
        DrawFormatString(0, 20, GRAY, "radian = %f", radian); // ���W�A���̒l��\��

        // ���W�v�Z
        int x = RADIUS * cos(radian); // ���w��x���W
        int y = RADIUS * sin(radian); // ���w��y���W
        int cx = x + WIDTH / 2; // �R���s���[�^�[��ʂ�x���W
        int cy = y + HEIGHT / 2; // �R���s���[�^�[��ʂ�y���W
        DrawBox(cx - 10, cy - 10, cx + 10, cy + 10, GetColor(0, 255, 255), TRUE); // �~�^�����镨��

        ScreenFlip(); // ����ʂ̓�e��\��ʂɔ��f������
        WaitTimer(16); // ��莞�ԑ҂�
        if (ProcessMessage() == -1) break; // Windows�������󂯎��G���[���N������I��
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; // ESC�L�[�������ꂽ��I��
    }

    DxLib_End(); // �c�w���C�u�����g�p�̏I������
    return 0; // �\�t�g�̏I��
}