#include "Effect.h"
#include "Myfunc.h"
#include "BoardManager.h"

class BoardManager;

Effect::Effect() {
	imgH_erase = LoadGraph("images\\erase.png");
	imgH_white = LoadGraph("images\\white.png");
}

Effect::~Effect()
{
}

void Effect::Update()
{
	return;
	if (type == "White" && state=="run") {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawExtendGraph_Ex(30 + x * 64,
			90+ y*64,
			30 + (x + 1) * 64,
			90 + (y + 1)*64,
			imgH_white,
			FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		alpha -= 10;
		if (alpha < 0) state = "complete";
	}
}

void Effect::Draw()
{
}
