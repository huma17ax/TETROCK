#include "BoardManager.h"
#include "DxLib.h"
#include "Myfunc.h"
#include "DxLib_KeyManager.h"

#include <queue>
#include <utility>
#include <algorithm>

BoardManager::BoardManager()
{
	board.resize(size_x, std::vector<int>(size_y, -1));
	scoreMap.resize(size_x, std::vector<int>(size_y, -1));
	//‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	LoadDivGraph("images\\blocks.png", 7, 7, 1, 64, 64, imgH_blocks);
	LoadDivGraph("images\\sign2.png", 4, 4, 1, 64, 64, imgH_signs);
	imgH_erase = LoadGraph("images\\erase.png");

	time = GetTime();
	score_time = GetTime();

	blockManager = new BlocksManager();
	blockManager->ownerBoard = this;
	blockManager->effectPtr = effectPtr;
}

BoardManager::BoardManager(int x, int y) {
	base_x = x;
	base_y = y;
	BoardManager();
}

BoardManager::~BoardManager()
{
	delete(blockManager);
}

double BoardManager::Update() {

	if (erase_flag == 1) {

		bool flag = false;
		for (int i = 0; i < erase_list.size(); i++) {
			erase_list[i]->x += 100;

			if (erase_list[i]->x > base_x + size_x * mass_size - 32) {
				erase_flag = -1;
				flag = true;
				break;
			}

		}

		if (flag == false) return 0.0;
		erase_list.clear();
	}

	if (blockManager->activeBlock.blockInit == 0) {
		if (keyManager.GetKeyState(KEY_INPUT_RIGHT) % 10 == 1) {
			blockManager->BlockMove(1);
			PlaySoundMem(sndH_button, DX_PLAYTYPE_BACK);
		}
		if (keyManager.GetKeyState(KEY_INPUT_RIGHT) == 31) {
			blockManager->BlockSlide(1);
			PlaySoundMem(sndH_button, DX_PLAYTYPE_BACK);
		}
		if (keyManager.GetKeyState(KEY_INPUT_LEFT) % 10 == 1) {
			blockManager->BlockMove(0);
			PlaySoundMem(sndH_button, DX_PLAYTYPE_BACK);
		}
		if (keyManager.GetKeyState(KEY_INPUT_LEFT) == 31) {
			blockManager->BlockSlide(0);
			PlaySoundMem(sndH_button, DX_PLAYTYPE_BACK);
		}
		if (keyManager.GetKeyState(KEY_INPUT_UP) == 1) {
			blockManager->BlockDown();
			PlaySoundMem(sndH_down, DX_PLAYTYPE_BACK);
			time = GetTime();
		}
		if (keyManager.GetKeyState(KEY_INPUT_DOWN) % 10 == 1) {
			blockManager->BlockFall();
			PlaySoundMem(sndH_button, DX_PLAYTYPE_BACK);
			time = GetTime();
		}
		if (keyManager.GetKeyState(KEY_INPUT_A) == 1) {
			blockManager->BlockRotate(0);
			PlaySoundMem(sndH_button, DX_PLAYTYPE_BACK);
		}
		//if (keyManager.GetKeyState(KEY_INPUT_D) == 1) blockManager->BlockRotate(1);
	}
	if (ElapsedTime(time) > 1000) {
		blockManager->BlockFall();
		time = GetTime();
	}

	LineErase();
	ScoreUpdate(false);

	blockManager->Update();

	if (gameover_flag == true) {
		return score + 0.00000001;
	}
	return 0.0;
}

void BoardManager::Draw() {

	for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) {
		if (board[i][j] >= 0) {
			DrawExtendGraph_Ex(base_x + i * mass_size, base_y + j*mass_size, base_x + (i + 1) * mass_size, base_y + (j + 1)*mass_size, imgH_blocks[board[i][j]], FALSE);
		}
	}

	DrawFormatStringToHandle(20, 10, GetColor(255, 0, 0), fontL, "Score : %.3f", score);

	for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) {
		if (scoreMap[i][j] >= 1) {
			if (GetBoardStatus(i, j - 1)) DrawExtendGraph_Ex(base_x + i * mass_size, base_y + j*mass_size, base_x + (i + 1) * mass_size, base_y + (j + 1)*mass_size, imgH_signs[0], TRUE);
			if (GetBoardStatus(i + 1, j)) DrawExtendGraph_Ex(base_x + i * mass_size, base_y + j*mass_size, base_x + (i + 1) * mass_size, base_y + (j + 1)*mass_size, imgH_signs[1], TRUE);
			if (GetBoardStatus(i, j + 1)) DrawExtendGraph_Ex(base_x + i * mass_size, base_y + j*mass_size, base_x + (i + 1) * mass_size, base_y + (j + 1)*mass_size, imgH_signs[2], TRUE);
			if (GetBoardStatus(i - 1, j)) DrawExtendGraph_Ex(base_x + i * mass_size, base_y + j*mass_size, base_x + (i + 1) * mass_size, base_y + (j + 1)*mass_size, imgH_signs[3], TRUE);
		}
	}

	DrawBox(500, 285, 970, 800, GetColor(255, 255, 255), FALSE);
	DrawFormatStringToHandle(500, 250, GetColor(255, 255, 255), fontS, "Space List");
	for (int i = 0; i < spaceCount.size(); i++) {
		DrawFormatStringToHandle(520, 300 + i * 30, GetColor(255, 255, 255), fontS, "size: %d  x %d : %.3fpt/block", spaceCount[i].first, spaceCount[i].second, 1.0 / spaceCount[i].first*spaceCount[i].second);
	}

	blockManager->Draw();

	for (int i = 0; i < erase_list.size(); i++) {
		DrawBox_Ex(base_x, base_y + erase_list[i]->pos_y*mass_size,
			base_x + erase_list[i]->x, base_y + (erase_list[i]->pos_y + 1)*mass_size,
			GetColor(0, 0, 0), TRUE);
		DrawExtendGraph_Ex(base_x + erase_list[i]->x - 64, base_y + erase_list[i]->pos_y*mass_size,
			base_x + erase_list[i]->x - 64 + 128, base_y + (erase_list[i]->pos_y + 1)*mass_size,
			imgH_erase, TRUE);
	}

	for (int i = 0; i < 11; i++) {
		DrawLine_Ex(base_x + i*mass_size, base_y, base_x + i*mass_size, base_y + size_y * mass_size, GetColor(100, 100, 100));
	}
	for (int i = 0; i < 21; i++) {
		DrawLine_Ex(base_x, base_y + i*mass_size, base_x + size_x * mass_size, base_y + i*mass_size, GetColor(100, 100, 100));
	}

}

bool BoardManager::GetBoardStatus(int x, int y) {

	if (x < 0 || x >= size_x || y < 0 || y >= size_y) {
		return true;
	}

	if (board[x][y] == -1) {
		return false;
	}
	else {
		return true;
	}

}

bool BoardManager::SetBoardStatus(int x, int y, int state) {

	if (x < 0 || x >= size_x || y < 0 || y >= size_y) {
		return false;
	}

	if (board[x][y] == -1) {
		board[x][y] = state;
		return true;
	}
	else {
		return false;
	}

}

void BoardManager::LineErase() {

	std::vector<int> full_lines;

	for (int i = 0; i < size_y; i++) {

		bool flag = true;
		for (int j = 0; j < size_x; j++) {
			if (board[j][i] == -1) flag = false;
		}

		if (flag == true) full_lines.emplace_back(i);

	}

	if (full_lines.size() == 0) return;

	if (erase_flag == 0) {
		EraseEffect* er = new EraseEffect();

		er->pos_y = full_lines[0];
		er->x = 0;

		erase_list.emplace_back(er);
		erase_flag = 1;
		PlaySoundMem(sndH_erase, DX_PLAYTYPE_BACK);
		return;
	}
	if (erase_flag == -1) erase_flag = 0;

	std::sort(full_lines.begin(), full_lines.end());

	for (int cnt = 0, i = size_y - 1; i >= 0; i--) {
		if (cnt < full_lines.size() && full_lines[cnt] == i) cnt++;

		for (int j = 0; j < size_x; j++) {
			if (i - cnt >= 0) {
				board[j][i] = board[j][i - cnt];
			}
			else {
				board[j][i] = -1;
			}
		}

	}

	for (int i = 0; i < full_lines.size(); i++) {
		owner->AddTime();
	}

}

void BoardManager::ScoreUpdate(bool addScore) {

	for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) {
		scoreMap[i][j] = -1;
	}
	std::vector<int> space;

	for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) {
		if (board[i][j] >= 0) scoreMap[i][j] = 0;
	}

	for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) {
		if (scoreMap[i][j] != -1) continue;

		//BFS
		bool isOpen = false;
		std::queue<std::pair<int, int>> Queue;
		Queue.push(std::make_pair(i, j));
		scoreMap[i][j] = 0;
		std::vector<std::pair<int, int>> group;

		while (Queue.size() != 0) {
			int x = Queue.front().first;
			int y = Queue.front().second;
			group.emplace_back(Queue.front());
			Queue.pop();

			if (y == 0) isOpen = true;

			if (x + 1 >= 0 && x + 1 < size_x && scoreMap[x + 1][y] == -1) {
				Queue.push(std::make_pair(x + 1, y));
				scoreMap[x + 1][y] = 0;
			}
			if (x - 1 >= 0 && x - 1 < size_x && scoreMap[x - 1][y] == -1) {
				Queue.push(std::make_pair(x - 1, y));
				scoreMap[x - 1][y] = 0;
			}
			if (y + 1 >= 0 && y + 1 < size_y && scoreMap[x][y + 1] == -1) {
				Queue.push(std::make_pair(x, y + 1));
				scoreMap[x][y + 1] = 0;
			}
			if (y - 1 >= 0 && y - 1 < size_y && scoreMap[x][y - 1] == -1) {
				Queue.push(std::make_pair(x, y - 1));
				scoreMap[x][y - 1] = 0;
			}

		}

		space.emplace_back((isOpen ? 0 : group.size()));
		for (int i = 0; i < group.size(); i++) {
			scoreMap[group[i].first][group[i].second] = (isOpen ? 0 : group.size());
		}

	}
	/*
	for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) {
		DrawFormatString(base_x + i * (mass_size - 20), base_y + j*(mass_size - 20), GetColor(255, 255, 255), "%d", scoreMap[i][j]);
	}
	*/

	spaceCount.resize(0);
	for (int i = 0; i < space.size(); i++) {
		if (space[i] != 0) {

			bool flag = false;
			for (int j = 0; j < spaceCount.size(); j++) {
				if (spaceCount[j].first == space[i]) {
					flag = true;
					spaceCount[j].second++;
					break;
				}
			}

			if (flag == false) {
				spaceCount.emplace_back(std::make_pair(space[i], 1));
			}

		}
	}

	sort(spaceCount.begin(), spaceCount.end(),
		[](const std::pair<int, int>& x, const std::pair<int, int> y) {return x.first < y.first; });


	if (addScore == false) return;

	for (int i = 0; i < space.size(); i++) {
		if (space[i] != 0) {
			score += (double)1 / space[i];
		}
	}

}

int BoardManager::GameOver() {
	/*
	if (board[3][0] >= 0 || board[4][0] >= 0 || board[5][0] >= 0 || board[6][0] >= 0) {
		gameover_flag = true;
		return 1;
	}
	else {
		return 0;
	}
	*/

	for (int cntX = 0, i = blockManager->activeBlock.pos_x; i < blockManager->activeBlock.pos_x + blockManager->activeBlock.shape.size_x; cntX++, i++)
		for (int cntY = 0, j = blockManager->activeBlock.pos_y; j < blockManager->activeBlock.pos_y + blockManager->activeBlock.shape.size_y; cntY++, j++) {

			if (blockManager->activeBlock.shape.arr[cntX][cntY] && GetBoardStatus(i, j)) {
				gameover_flag = true;
				return 1;
			}

		}
	return 0;
}