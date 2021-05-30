#include "DxLib.h"
#include "BlocksManager.h"
#include "SceneManager.h"
#include "Myfunc.h"
#include "DxLib_KeyManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	dvlp_x = 1400;
	dvlp_y = 1400;
	rls_x = 980;
	rls_y = 980;

	ChangeWindowMode(TRUE);
	SetGraphMode(rls_x, rls_y,16);
	SetBackgroundColor(0, 0, 0);
	SetAlwaysRunFlag(TRUE);
	if (DxLib_Init() == -1) { return -1; }// �c�w���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK);
	SetMainWindowText("TETROCK");

	SceneManager sceneManager;

	while (1) {
		SetBackgroundColor(0, 0, 0);
		ClearDrawScreen();

		keyManager.Update();
		sceneManager.Draw();
		if (sceneManager.Update() == true) break;

		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		ScreenFlip();
	}

	sceneManager.ScoreReserve();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}
