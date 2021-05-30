#include "SceneManager.h"
#include "DxLib.h"
#include "Myfunc.h"
#include <fstream>
#include "DxLib_KeyManager.h"

class Title;
class GameManager;

SceneManager::SceneManager()
{
	scene = Title_Scene;

	std::ifstream ifs("./conlog.bin", std::ios::in | std::ios::binary);
	ifs.read((char*)&high_score, sizeof(double));
	ifs.close();

	title = new Title(high_score);
	gameManager = new GameManager();

	PlaySoundMem(sndH_bgm, DX_PLAYTYPE_LOOP);

}

SceneManager::~SceneManager()
{
}

void SceneManager::ScoreReserve() {

	std::ofstream ofs("./conlog.bin", std::ios::out | std::ios::binary | std::ios::trunc);
	ofs.write((char*)&high_score, sizeof(double));
	ofs.close();
}

bool SceneManager::Update()
{

	double state=0.0;
	int title_return;

	switch (scene)
	{
	case Title_Scene:
		title_return = title->Update();
		if (title_return == 1) {
			delete(gameManager);
			gameManager = new GameManager();
			gameManager->high_score = high_score;
			scene = Game_Scene;
			PlaySoundMem(sndH_enter, DX_PLAYTYPE_BACK);
			WaitTimer(500);
		}
		if (title_return == 2) {
			end_flag = true;
		}
		break;

	case Game_Scene:
		state = gameManager->Update();
		if (state > 0) {

			if (high_score < state) {
				high_score = state;
			}

			delete(title);
			title = new Title(high_score);
			scene = Title_Scene;
		}
		
		break;

	default:
		break;
	}

	if (keyManager.GetKeyState(KEY_INPUT_RSHIFT) >= 1
		&& keyManager.GetKeyState(KEY_INPUT_LSHIFT) >= 1) {
		high_score = 0.0;
	}


	return end_flag;
}

void SceneManager::Draw() {

	switch (scene)
	{
	case Title_Scene:
		title->Draw();
		break;

	case Game_Scene:
		gameManager->Draw();
		break;

	default:
		break;
	}

}