#include "Title.h"
#include "DxLib.h"
#include "Myfunc.h"
#include "DxLib_KeyManager.h"

Title::Title()
{
}

Title::Title(double score) {
	high_score = score;
	LoadDivGraph("images\blocks.png", 5, 5, 1, 64, 64, imgH_blocks);
	imgH_title = LoadGraph("images\\title.png");
	imgH_start = LoadGraph("images\\title_sub2.png");
	imgH_quit = LoadGraph("images\\title_sub1.png");
}

Title::~Title()
{
}

void Title::Draw() {
	DrawExtendGraph_Ex(100, 200, 1300, 392, imgH_title, TRUE);
	if (select == 0) {
		DrawExtendGraph_Ex(320, 758, 1130, 930, imgH_start, TRUE);
		DrawExtendGraph_Ex(410, 1000, 1035, 1168, imgH_quit, TRUE);
	}
	else {
		DrawExtendGraph_Ex(350, 770, 1100, 930, imgH_start, TRUE);
		DrawExtendGraph_Ex(386, 986, 1059, 1168, imgH_quit, TRUE);
	}
	DrawFormatStringToHandle(170, 330, GetColor(255, 255, 255), fontL ,"HighScore : %.3fpt", high_score);
	
	DrawFormatStringToHandle(700,950, GetColor(255, 255, 255), fontS ,"press ª« & Enter");

}

int Title::Update() {

	if (keyManager.GetKeyState(KEY_INPUT_RETURN) >= 1) {
		if (select == 0) {
			return 1;
		}
		else {
			return 2;
		}
	}

	if (keyManager.GetKeyState(KEY_INPUT_UP) == 1) {
		select = 0;
	}

	if (keyManager.GetKeyState(KEY_INPUT_DOWN) == 1) {
		select = 1;
	}
	

	return 0;
}