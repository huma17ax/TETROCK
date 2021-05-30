#include "GameManager.h"
#include "Myfunc.h"

GameManager::GameManager()
{

	imgH_shade = LoadGraph("images\\shade.png");

	effectManager = new EffectManager();

	player1 = new BoardManager();

	player1->base_x = 30;player1->base_y = 90;
	player1->right_key = KEY_INPUT_RIGHT; player1->left_key = KEY_INPUT_LEFT;
	player1->down_key = KEY_INPUT_DOWN; player1->rotate_key = KEY_INPUT_A;

	player1->effectPtr = effectManager;
	player1->owner = this;
}

GameManager::~GameManager()
{
	delete(player1);
}

void GameManager::Draw() {

	DrawFormatStringToHandle(500, 10, GetColor(255, 0, 0), fontL ,"Žc‚èŽžŠÔ : %d", game_time);

	player1->Draw();
	effectManager->Draw();
}

double GameManager::Update() {

	if (ElapsedTime(subtime) >= 1000) {
		game_time--;
		subtime = GetTime();
	}

	if (game_time == 0) {
		player1->gameover_flag = true;
		player1->timeup_flag = true;
	}

	double state = player1->Update();

	if (state > 0) {
		DrawExtendGraph_Ex(0, 0, 1400, 1400, imgH_shade, TRUE);

		DrawBox(250, 250, 250 + 480, 250 + 480, GetColor(0, 0, 0), TRUE);

		if (player1->timeup_flag) {
			DrawFormatStringToHandle(400, 320, GetColor(255, 0, 0), fontL, "Time Over");
		}
		else {
			DrawFormatStringToHandle(400, 320, GetColor(255, 0, 0), fontL, "Game Over");
		}
		DrawFormatStringToHandle(370, 380, GetColor(255, 255, 0), fontL ,"Score: %.3f", state);
		if (high_score < state) {
			DrawFormatStringToHandle(380, 460, GetColor(255, 255, 0), fontL, "HighScore!!");
		}
		PlaySoundMem(sndH_over, DX_PLAYTYPE_BACK);
		ScreenFlip();
		WaitTimer(4000);
	}

	effectManager->Update();

	return state;
}

void GameManager::AddTime() {
	game_time++;
}