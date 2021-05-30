#pragma once
#include "BlocksManager.h"
#include "EffectManager.h"
#include <utility>
#include "GameManager.h"

class BlocksManager;
class EffectManager;
class GameManager;

typedef struct {
	int x;
	int pos_y;
}EraseEffect;

class BoardManager
{
public:
	BoardManager();
	BoardManager(int, int);
	~BoardManager();

	double Update();
	void Draw();

	bool GetBoardStatus(int,int);
	bool SetBoardStatus(int,int,int);
	void ScoreUpdate(bool);
	int GameOver();

	static const int size_x = 10;
	static const int size_y = 20;
	static const int mass_size = 64;
	int base_x = 30, base_y = 90;

	int right_key;
	int left_key;
	int down_key;
	int rotate_key;

	int time;
	int score_time;
	double score;

	EffectManager* effectPtr;
	GameManager* owner;

	bool gameover_flag = false;
	bool timeup_flag = false;

	std::vector<EraseEffect*> erase_list;
	int erase_flag = 0;

private:

	BlocksManager *blockManager;

	int imgH_blocks[7];
	int imgH_signs[4];
	int imgH_erase;

	int sndH_button = LoadSoundMem("sounds\\button.mp3");
	int sndH_down = LoadSoundMem("sounds\\down.mp3");
	int sndH_erase = LoadSoundMem("sounds\\erase.mp3");

	std::vector<std::vector<int>> board;
	std::vector<std::vector<int>> scoreMap;
	std::vector<std::pair<int, int>> spaceCount;

	void LineErase();

	int fontL = CreateFontToHandle("MS Pゴシック", 40, 5, DX_FONTTYPE_NORMAL);
	int fontS = CreateFontToHandle("MS Pゴシック", 30, 4, DX_FONTTYPE_NORMAL);

};