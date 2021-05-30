#pragma once
#include "DxLib.h"
#include <algorithm>
#include <vector> 

class KeyManager
{
public:
	KeyManager();
	~KeyManager();

	//キー情報の更新
	void Update();

	//キー情報の取得 -1...離した瞬間 0...押していない 1...押した瞬間 2以上...押している
	int GetKeyState(int);

private:
	std::vector<long long int> keyStates;
	char Buf[256];

};

extern KeyManager keyManager;