#include "DxLib_KeyManager.h"

KeyManager keyManager;

KeyManager::KeyManager()
{
	keyStates.resize(256, 0);
}

KeyManager::~KeyManager()
{
}

void KeyManager::Update()
{
	GetHitKeyStateAll(Buf);

	for (int i = 0; i < 256; i++) {

		if (Buf[i] == 1) {
			if (keyStates[i] <= 0) {
				keyStates[i] = 1;
				continue;
			}
			if (keyStates[i] >= 1) {
				keyStates[i] += 1;
				continue;
			}
		}
		else {
			if (keyStates[i] == -1) {
				keyStates[i] = 0;
				continue;
			}
			if (keyStates[i] > 0) {
				keyStates[i] = -1;
				continue;
			}
		}

	}

	return;
}

int KeyManager::GetKeyState(int keycode)
{
	if (keycode < 0 || keycode >= 256) {
		return 0;
	}

	return keyStates[keycode];
}
