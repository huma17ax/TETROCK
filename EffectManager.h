#pragma once
#include <vector>
#include "Effect.h"
#include <string>

class Effect;

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	bool effect_flag = false;

	void AddEffect(int,int,int);
	void Update();
	void Draw();

	std::vector<int> effect_list;
private:

};
