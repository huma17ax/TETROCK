#include "EffectManager.h"
#include <vector>

class Effect;

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Update()
{
	/*
	for (int i = 0; i < effect_list.size(); i++) {
		//effect_list[i]->Update();
	}

	for (int i = 0; i < effect_list.size(); i++) {
		//if (effect_list[i]->state == "complete") {
			//effect_list.erase(effect_list.begin() + i);
			//i--;
		//}
	}
	*/

	AddEffect(0, 0, 0);

}

void EffectManager::Draw()
{
	/*
	for (int i = 0; i < effect_list.size(); i++) {
		//effect_list[i]->Draw();
	}
	*/
}

void EffectManager::AddEffect(int _type,int _x,int _y)
{
	//Effect* ef = new Effect();
	/*
	if (_type == 0) {
		ef->type = "White";
		ef->state = "run";
		ef->x = _x;
		ef->y = _y;
		ef->alpha = 255;
	}
	*/

	//effect_list.push_back(new Effect());
	//effect_list.resize(1);
	//effect_list[0] = 1;
}