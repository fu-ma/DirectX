#include "Framework.h"

void Framework::GameRun()
{
	staticInit();
	while (true)//ゲームループ
	{
		if (SceneTime == 0)
		{
			Init();
		}
		if (Update() == false)
		{
			break;
		}
		if (SceneTime)
		{
			Draw();
		}
	}
	SceneDelete();
}

void Framework::staticInit()
{
	winApp = std::make_unique<WinApp>();
	common = std::make_unique<DirectXCommon>(winApp.get());
	winApp->Innitialize();
	common->Initialize();
	input = Input::GetInstance();
	input->Initialize(winApp->GetHInstance(), winApp->GetHwnd());
	Audio::Init();
	//ライト静的初期化
	LightGroup::StaticInitialize(common->GetDev().Get());
	/*スプライト初期化*/
	Sprite::StaticInitialize(common->GetDev().Get(), WinApp::window_width, WinApp::window_height);
	Sprite::LoadTexture(0, L"Resources/debugfont.png");
	debugText = DebugText::GetInstance();
	debugText->Initialize(0);

	/*FBX初期化*/
	FbxLoader::GetInstance()->Initialize(common->GetDev().Get());

	/*モデル初期化*/
	ModelObj::StaticInitialize(common->GetDev().Get());
	// カメラ生成
	camera = std::make_unique<DebugCamera>(WinApp::window_width, WinApp::window_height, input);
	// パーティクルマネージャ初期化
	ParticleManager::GetInstance()->Initialize(common->GetDev().Get());
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera.get());
}

void Framework::Init()
{
}

bool Framework::Update()
{
	//キーボード情報の取得開始
	input->Update();
	if (winApp->ProcessMessage() || input->isKeyTrigger(DIK_ESCAPE))
	{
		return false;
	}

	return true;
}

void Framework::Draw()
{
}
