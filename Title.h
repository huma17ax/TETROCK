#pragma once
#include "DxLib.h"

class Title
{
public:
	Title();
	Title(double);
	~Title();

	void Draw();
	int Update();

	int select=0;

private:

	int imgH_blocks[5];
	int imgH_title;
	int imgH_start;
	int imgH_quit;

	double high_score;

	int fontL = CreateFontToHandle("MS P�S�V�b�N", 55, 5);
	int fontS = CreateFontToHandle("MS P�S�V�b�N", 30, 5);

};