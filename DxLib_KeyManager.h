#pragma once
#include "DxLib.h"
#include <algorithm>
#include <vector> 

class KeyManager
{
public:
	KeyManager();
	~KeyManager();

	//�L�[���̍X�V
	void Update();

	//�L�[���̎擾 -1...�������u�� 0...�����Ă��Ȃ� 1...�������u�� 2�ȏ�...�����Ă���
	int GetKeyState(int);

private:
	std::vector<long long int> keyStates;
	char Buf[256];

};

extern KeyManager keyManager;