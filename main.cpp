#include"GameScene.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Framework *scene = new GameScene();

	scene->GameRun();

	delete scene;
	scene = nullptr;
	return 0;
}