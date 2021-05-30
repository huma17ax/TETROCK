#pragma once
#include "BoardManager.h"
#include "EffectManager.h"
#include "Myfunc.h"

class BoardManager;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Draw();
	double Update();

	void AddTime();

	int high_score;

private:

	BoardManager* player1;
	EffectManager* effectManager;
	int game_time = 150;
	int subtime = GetTime();

	int imgH_shade;
	int sndH_over = LoadSoundMem("sounds\\gameover.mp3");

	int fontL = CreateFontToHandle("MS PÉSÉVÉbÉN", 40, 5);

};