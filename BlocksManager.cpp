#include "BlocksManager.h"
#include <fstream>
#include <string>
#include "Myfunc.h"
#include "DxLib.h"
#include "BoardManager.h"

BlocksManager::BlocksManager()
{
	//画像の読み込み
	LoadDivGraph("images\\blocks.png", 7, 7, 1, 64, 64, imgH_blocks);

	imgH_white = LoadGraph("images\\white.png");

	//block_statusファイルから読み込み

	std::ifstream input;
	input.open("block_status.txt");

	while (!input.eof()) {

		BlockShape* bs = new BlockShape();

		input >> bs->size_x >> bs->size_y;

		bs->arr.resize(bs->size_x, std::vector<bool>(bs->size_y));


		for (int j = 0; j < bs->size_y; j++) for (int k = 0; k < bs->size_x; k++) {
			int in;
			input >> in;
			bs->arr[k][j] = (in == 1 ? true : false);
		}

		blockTypes.emplace_back(bs);

	}
	input.close();


	GenNewBlock();
	preblock_type = GetRand(6);

}

BlocksManager::~BlocksManager()
{
	for (int i = 0; i < blockTypes.size(); i++) {
		delete(blockTypes[i]);
	}
}

void BlocksManager::BlockRotate(int way) {

	//現状を一時記憶
	BlockState _stored = activeBlock;

	switch (activeBlock.type)
	{
	case 0://I
		if (activeBlock.rot == 0) {//横→縦
			activeBlock.rot = 1;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y, false));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x + 1;
			activeBlock.pos_y = _stored.pos_y - 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x + 2;
			activeBlock.pos_y = _stored.pos_y - 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x + 1;
			activeBlock.pos_y = _stored.pos_y - 2;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x + 2;
			activeBlock.pos_y = _stored.pos_y - 2;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;
		}
		else {//縦→横
			activeBlock.rot = 0;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x - 1;
			activeBlock.pos_y = _stored.pos_y + 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x - 2;
			activeBlock.pos_y = _stored.pos_y + 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x - 1;
			activeBlock.pos_y = _stored.pos_y + 2;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x - 2;
			activeBlock.pos_y = _stored.pos_y + 2;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;
		}
		break;
	case 1://J
		if (activeBlock.rot == 0) {//下凸→左凸
			activeBlock.rot = 1;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i ^ 1][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y - 1;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		else if (activeBlock.rot == 1) {//左凸→上凸
			activeBlock.rot = 2;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[(i == 0 ? 2 : (i == 1 ? 1 : 0))][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		else if (activeBlock.rot == 2) {//上凸→右凸
			activeBlock.rot = 3;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i ^ 1][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x + 1;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		else {//右凸→下凸
			activeBlock.rot = 0;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[(i == 0 ? 2 : (i == 1 ? 1 : 0))][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x - 1;
			activeBlock.pos_y = _stored.pos_y + 1;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		break;
	case 2://L
		if (activeBlock.rot == 0) {//下凸→左凸
			activeBlock.rot = 1;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i ^ 1][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y - 1;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		else if (activeBlock.rot == 1) {//左凸→上凸
			activeBlock.rot = 2;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[(i == 0 ? 2 : (i == 1 ? 1 : 0))][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;
		}
		else if (activeBlock.rot == 2) {//上凸→右凸
			activeBlock.rot = 3;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i ^ 1][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x + 1;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		else {//右凸→下凸
			activeBlock.rot = 0;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[(i == 0 ? 2 : (i == 1 ? 1 : 0))][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x - 1;
			activeBlock.pos_y = _stored.pos_y + 1;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		break;
	case 3://S
		if (activeBlock.rot == 0) {//横→縦
			activeBlock.rot = 1;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i ^ 1][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y - 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x + 1;
			activeBlock.pos_y = _stored.pos_y - 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x + 1;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;
		}
		else {//縦→横
			activeBlock.rot = 0;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i][j] = _stored.shape.arr[j ^ 1][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y + 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x - 1;
			activeBlock.pos_y = _stored.pos_y + 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x - 1;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;
		}
		break;
	case 4://Z
		if (activeBlock.rot == 0) {//横→縦
			activeBlock.rot = 1;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i ^ 1][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y - 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x + 1;
			activeBlock.pos_y = _stored.pos_y - 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x + 1;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;
		}
		else {//縦→横
			activeBlock.rot = 0;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i][j] = _stored.shape.arr[j ^ 1][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y + 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x - 1;
			activeBlock.pos_y = _stored.pos_y + 1;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock.pos_x = _stored.pos_x - 1;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		break;
	case 5://T
		if (activeBlock.rot == 0) {//下凸→左凸
			activeBlock.rot = 1;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i ^ 1][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y - 1;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		else if (activeBlock.rot == 1) {//左凸→上凸
			activeBlock.rot = 2;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[(i == 0 ? 2 : (i == 1 ? 1 : 0))][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		else if (activeBlock.rot == 2) {//上凸→右凸
			activeBlock.rot = 3;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[i ^ 1][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x + 1;
			activeBlock.pos_y = _stored.pos_y;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		else {//右凸→下凸
			activeBlock.rot = 0;

			//形状変更
			activeBlock.shape.size_x = _stored.shape.size_y;
			activeBlock.shape.size_y = _stored.shape.size_x;
			activeBlock.shape.arr.clear();
			activeBlock.shape.arr.resize(activeBlock.shape.size_x, std::vector<bool>(activeBlock.shape.size_y));

			for (int i = 0; i < activeBlock.shape.size_x; i++)
				for (int j = 0; j < activeBlock.shape.size_y; j++) {
					activeBlock.shape.arr[(i == 0 ? 2 : (i == 1 ? 1 : 0))][j] = _stored.shape.arr[j][i];
				}

			//位置調整
			activeBlock.pos_x = _stored.pos_x - 1;
			activeBlock.pos_y = _stored.pos_y + 1;
			if (BlockOverlap() == false) return;

			activeBlock = _stored;

		}
		break;
	case 6://O
		break;
	default:
		break;
	}

	return;
}

void BlocksManager::BlockDown() {

	while (1) {

		//下に底がある判定
		if (activeBlock.pos_y + activeBlock.shape.size_y >= BoardManager::size_y) {
			BlockRegist();
			GenNewBlock();
			return;
		}

		//下にブロックがある判定
		bool flag = true;
		for (int cntX = 0, i = activeBlock.pos_x; i < activeBlock.pos_x + activeBlock.shape.size_x; cntX++, i++)
			for (int cntY = 0, j = activeBlock.pos_y; j < activeBlock.pos_y + activeBlock.shape.size_y; cntY++, j++) {

				if (activeBlock.shape.arr[cntX][cntY] && ownerBoard->GetBoardStatus(i, j + 1)) {
					flag = false;
					break;
				}

			}
		if (flag == false) {
			BlockRegist();
			GenNewBlock();
			return;
		}

		activeBlock.pos_y++;

	}
	return;
}

void BlocksManager::BlockFall() {

	//下に底がある判定
	if (activeBlock.pos_y + activeBlock.shape.size_y >= BoardManager::size_y) {
		BlockRegist();
		GenNewBlock();
		return;
	}

	//下にブロックがある判定
	bool flag = true;
	for (int cntX = 0, i = activeBlock.pos_x; i < activeBlock.pos_x + activeBlock.shape.size_x; cntX++, i++)
		for (int cntY = 0, j = activeBlock.pos_y; j < activeBlock.pos_y + activeBlock.shape.size_y; cntY++, j++) {

			if (activeBlock.shape.arr[cntX][cntY] && ownerBoard->GetBoardStatus(i, j + 1)) {
				flag = false;
				break;
			}

		}
	if (flag == false) {
		BlockRegist();
		GenNewBlock();
		return;
	}

	activeBlock.pos_y++;
	return;
}

void BlocksManager::BlockMove(int way) {
	if (way) {//右

		//右にブロックがある判定
		bool flag = true;
		for (int cntX = 0, i = activeBlock.pos_x; i < activeBlock.pos_x + activeBlock.shape.size_x; cntX++, i++)
			for (int cntY = 0, j = activeBlock.pos_y; j < activeBlock.pos_y + activeBlock.shape.size_y; cntY++, j++) {

				if (activeBlock.shape.arr[cntX][cntY] && ownerBoard->GetBoardStatus(i + 1, j)) {
					flag = false;
					break;
				}

			}
		if (flag == false) return;

		if (activeBlock.pos_x + activeBlock.shape.size_x < BoardManager::size_x) activeBlock.pos_x++;


	}
	else {//左

		//左にブロックがある判定
		bool flag = true;
		for (int cntX = 0, i = activeBlock.pos_x; i < activeBlock.pos_x + activeBlock.shape.size_x; cntX++, i++)
			for (int cntY = 0, j = activeBlock.pos_y; j < activeBlock.pos_y + activeBlock.shape.size_y; cntY++, j++) {

				if (activeBlock.shape.arr[cntX][cntY] && ownerBoard->GetBoardStatus(i - 1, j)) {
					flag = false;
					break;
				}

			}
		if (flag == false) return;

		if (activeBlock.pos_x > 0) activeBlock.pos_x--;


	}
}

void BlocksManager::BlockSlide(int way) {
	if (way) {//右

		while (1) {
			//右にブロックがある判定
			bool flag = true;
			for (int cntX = 0, i = activeBlock.pos_x; i < activeBlock.pos_x + activeBlock.shape.size_x; cntX++, i++)
				for (int cntY = 0, j = activeBlock.pos_y; j < activeBlock.pos_y + activeBlock.shape.size_y; cntY++, j++) {

					if (activeBlock.shape.arr[cntX][cntY] && ownerBoard->GetBoardStatus(i + 1, j)) {
						flag = false;
						break;
					}

				}
			if (flag == false) return;

			if (activeBlock.pos_x + activeBlock.shape.size_x < BoardManager::size_x) {
				activeBlock.pos_x++;
			}
			else {
				return;
			}
		}

	}
	else {//左

		while (1) {
			//左にブロックがある判定
			bool flag = true;
			for (int cntX = 0, i = activeBlock.pos_x; i < activeBlock.pos_x + activeBlock.shape.size_x; cntX++, i++)
				for (int cntY = 0, j = activeBlock.pos_y; j < activeBlock.pos_y + activeBlock.shape.size_y; cntY++, j++) {

					if (activeBlock.shape.arr[cntX][cntY] && ownerBoard->GetBoardStatus(i - 1, j)) {
						flag = false;
						break;
					}

				}
			if (flag == false) return;

			if (activeBlock.pos_x > 0) {
				activeBlock.pos_x--;
			}
			else {
				return;
			}

		}
	}
}

void BlocksManager::BlockRegist() {

	for (int cntX = 0, i = activeBlock.pos_x; i < activeBlock.pos_x + activeBlock.shape.size_x; cntX++, i++)
		for (int cntY = 0, j = activeBlock.pos_y; j < activeBlock.pos_y + activeBlock.shape.size_y; cntY++, j++) {

			if (activeBlock.shape.arr[cntX][cntY]) {
				ownerBoard->SetBoardStatus(i, j, activeBlock.type);
				//effectPtr->AddEffect(0, i, j);
				WhiteEffect* ef = new WhiteEffect();

				ef->pos_x = i;
				ef->pos_y = j;
				ef->alpha = 255;

				white_list.emplace_back(ef);
			}

		}

	//int flag = ownerBoard->GameOver();

	//if (flag == 1) return;

	ownerBoard->ScoreUpdate(true);

	return;
}

void BlocksManager::Draw() {

	/*
	int base=0;

	for (int k = 0; k < blockTypes.size(); k++) {

	for (int i = 0; i < blockTypes[k]->size_y; i++) {
	for (int j = 0; j < blockTypes[k]->size_x; j++) {

	if (blockTypes[k]->arr[j][i] == true) {
	DrawExtendGraph_Ex(base + j * 64, i * 64, base + j * 64 + 64, i * 64 + 64, imgH_blocks[k % 5], FALSE);
	}

	}
	}
	base = base + blockTypes[k]->size_x*64;
	}
	*/

	if (activeBlock.blockInit % 2 == 0) {

		for (int cntX = 0, i = activeBlock.pos_x; i < activeBlock.pos_x + activeBlock.shape.size_x; cntX++, i++)
			for (int cntY = 0, j = activeBlock.pos_y; j < activeBlock.pos_y + activeBlock.shape.size_y; cntY++, j++) {

				if (activeBlock.shape.arr[cntX][cntY]) {
					DrawExtendGraph_Ex(ownerBoard->base_x + i * ownerBoard->mass_size,
						ownerBoard->base_y + j*ownerBoard->mass_size,
						ownerBoard->base_x + (i + 1) * ownerBoard->mass_size,
						ownerBoard->base_y + (j + 1)*ownerBoard->mass_size,
						imgH_blocks[activeBlock.type],
						FALSE);
				}
			}

	}

	DrawFormatStringToHandle(500,100, GetColor(255, 255, 255), font ,"Next:");

	for (int cntX = 0, i = 0; i < blockTypes[preblock_type]->size_x; cntX++, i++)
		for (int cntY = 0, j = 0; j < blockTypes[preblock_type]->size_y; cntY++, j++) {

			if (blockTypes[preblock_type]->arr[cntX][cntY]) {
				DrawExtendGraph_Ex(ownerBoard->base_x + ownerBoard->size_x*ownerBoard->mass_size + i * 48 + 100,
					ownerBoard->base_y + j*48 + 100,
					ownerBoard->base_x + ownerBoard->size_x*ownerBoard->mass_size + (i + 1) * 48+ 100,
					ownerBoard->base_y + (j + 1)*48+100,
					imgH_blocks[preblock_type],
					FALSE);
			}
		}


	for (int i = 0; i < white_list.size(); i++) {

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, white_list[i]->alpha);
		DrawExtendGraph_Ex(ownerBoard->base_x + white_list[i]->pos_x* ownerBoard->mass_size,
			ownerBoard->base_y + white_list[i]->pos_y*ownerBoard->mass_size,
			ownerBoard->base_x + (white_list[i]->pos_x+ 1) * ownerBoard->mass_size,
			ownerBoard->base_y + (white_list[i]->pos_y + 1)*ownerBoard->mass_size,
			imgH_white,
			FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

void BlocksManager::GenNewBlock() {

	activeBlock.type = preblock_type;
	preblock_type = GetRand(6);

	activeBlock.shape = *blockTypes[activeBlock.type];
	activeBlock.rot = 0;
	activeBlock.pos_y = 0;
	activeBlock.pos_x = 3;
	activeBlock.blockInit = 10;

	switch (activeBlock.type)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		break;
	}

}

bool BlocksManager::BlockOverlap() {

	for (int cntX = 0, i = activeBlock.pos_x; i < activeBlock.pos_x + activeBlock.shape.size_x; cntX++, i++)
		for (int cntY = 0, j = activeBlock.pos_y; j < activeBlock.pos_y + activeBlock.shape.size_y; cntY++, j++) {

			if (activeBlock.shape.arr[cntX][cntY] && ownerBoard->GetBoardStatus(i, j)) {
				return true;
			}

			if (i < 0 || j < 0 || i >= ownerBoard->size_x || j >= ownerBoard->size_y) {
				return true;
			}
		}

	return false;
}

void BlocksManager::Update() {
	if (activeBlock.blockInit > 0) activeBlock.blockInit--;
	if (activeBlock.blockInit == 1) {
		ownerBoard->GameOver();
	}

	for (int i = 0; i < white_list.size(); i++) {

		if (ownerBoard->erase_flag != 0) white_list[i]->alpha = 0;

		white_list[i]->alpha -= 10;

		if (white_list[i]->alpha < 0) {
			white_list.erase(white_list.begin() + i);
			i--;
		}
	}
}