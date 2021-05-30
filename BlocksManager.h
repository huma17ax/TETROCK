#pragma once
#include <vector>
#include "BoardManager.h"
#include "EffectManager.h"

class BoardManager;
class EffectManager;

typedef struct {

	int size_x, size_y;
	int cent_x, cent_y;

	std::vector<std::vector<bool>> arr;

}BlockShape;

typedef struct {

	BlockShape shape;
	int pos_x, pos_y;//ブロックの左上マス
	int rot;//出現時が0 右回転ごとに+1
	int type;//typestatusの上から0
	int blockInit;//新しいブロック

}BlockState;

typedef struct {

	int pos_x, pos_y;
	int alpha;

}WhiteEffect;

class BlocksManager
{
public:
	BlocksManager();
	~BlocksManager();

	std::vector<BlockShape*> blockTypes;

	BlockState activeBlock;

	BoardManager* ownerBoard;
	EffectManager* effectPtr;

	void BlockRotate(int);
	void BlockDown();//最下層まで落下
	void BlockFall();//通常の1マス落下
	void BlockMove(int);//1マス左右移動
	void BlockSlide(int);//左右最端移動

	void Update();
	void Draw();


private:

	int imgH_blocks[7];
	int imgH_white;
	void GenNewBlock();
	void BlockRegist();
	bool BlockOverlap();//重なり判定

	int font = CreateFontToHandle("MS Pゴシック", 30, 5);

	int preblock_type;

	std::vector<WhiteEffect*> white_list;

};