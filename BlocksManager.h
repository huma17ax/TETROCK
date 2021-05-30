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
	int pos_x, pos_y;//�u���b�N�̍���}�X
	int rot;//�o������0 �E��]���Ƃ�+1
	int type;//typestatus�̏ォ��0
	int blockInit;//�V�����u���b�N

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
	void BlockDown();//�ŉ��w�܂ŗ���
	void BlockFall();//�ʏ��1�}�X����
	void BlockMove(int);//1�}�X���E�ړ�
	void BlockSlide(int);//���E�Œ[�ړ�

	void Update();
	void Draw();


private:

	int imgH_blocks[7];
	int imgH_white;
	void GenNewBlock();
	void BlockRegist();
	bool BlockOverlap();//�d�Ȃ蔻��

	int font = CreateFontToHandle("MS P�S�V�b�N", 30, 5);

	int preblock_type;

	std::vector<WhiteEffect*> white_list;

};