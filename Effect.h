#pragma once
#include "DxLib.h"
#include <string>

class Effect
{
public:
	Effect();
	Effect(std::string,int);
	Effect(std::string, int, int);
	~Effect();

	void Update();
	void Draw();

	int y;
	int x = 0;

	std::string type;
	std::string state;
	int alpha;

private:

	int imgH_erase;
	int imgH_white;

};