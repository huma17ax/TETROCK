#pragma once
#include "GameManager.h"
#include "Title.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool Update();
	void Draw();

	void ScoreReserve();

private:

	GameManager* gameManager;
	Title* title;

	enum Scene
	{
		Title_Scene,
		Game_Scene
	} scene;

	double high_score;

	int sndH_bgm = LoadSoundMem("sounds\\bgm.mp3");
	int sndH_enter = LoadSoundMem("sounds\\enter.mp3");

	bool end_flag = false;

};