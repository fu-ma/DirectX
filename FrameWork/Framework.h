#pragma once
#include"WindowAPI.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "DebugText.h"
#include "DebugCamera.h"
#include "Audio.h"
#include "ParticleManager.h"
#include"ModelObj.h"
#include"LightGroup.h"
#include"FbxLoader.h"

#include<memory>

/// <summary>
/// フレームワーク
/// </summary>
class Framework
{
protected:
	using WinPtr = std::unique_ptr<WinApp>;
	using CommonPtr = std::unique_ptr<DirectXCommon>;
	using AudioPtr = std::unique_ptr<Audio>;
	using DebugCamPtr = std::unique_ptr<DebugCamera>;
	using LightGroupPtr = std::unique_ptr<LightGroup>;
	enum class GameSceneNo
	{
		Title,
		GamePlay,
		End,
	};

public:

	/// <summary>
	/// 実行
	/// </summary>
	void GameRun();

	/// <summary>
	/// 最初だけ初期化
	/// </summary>
	virtual void staticInit();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init();

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	virtual bool Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void SceneDelete()
	{
#pragma region 解放処理
		//FBXの解放処理
		FbxLoader::GetInstance()->Finalize();

		//XAudio2解放
		Audio::xAudio2.Reset();
		//WindowsAPIの終了処理
		winApp->Finalize();
	};

	const int &SceneTimeGetter() { return SceneTime; }
protected:
	WinPtr winApp;
	Input* input;
	CommonPtr common;

	AudioPtr audio;
	DebugText *debugText;
	ParticleManager *particleMan;
	DebugCamPtr camera;

	LightGroupPtr lightGroup;

	//現在のシーンの番号
	int SceneNo = static_cast<int>(GameSceneNo::Title);
	//初期化のための計測
	int SceneTime = 0;
};

