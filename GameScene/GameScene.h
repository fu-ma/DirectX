#pragma once
#include"ModelObj.h"
#include"Model.h"
#include"CollisionPrimitive.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include"LightGroup.h"
#include"Framework.h"
#include"CollisionManager.h"
#include "Player.h"
#include "TouchableObject.h"

class GameScene : public Framework
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
	using ObjPtr = std::unique_ptr<ModelObj>;
	using ModelPtr = std::unique_ptr<Model>;
	using SpritePtr = std::unique_ptr<Sprite>;

private:

	SoundData soundData1;
	SoundData soundData2;
	SoundData soundData3;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	Sprite *spriteBG = nullptr;

	Model *modelSkydome = nullptr;
	Model *modelGround = nullptr;
	Model *modelFighter = nullptr;
	Model *modelSphere = nullptr;

	ModelObj *objSkydome = nullptr;
	TouchableObject *objGround = nullptr;
	Player *objFighter = nullptr;
	ModelObj *objSphere = nullptr;

	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.3f,0.1f,0.1f };

	float spotLightDir[3] = { 0,-1,0 };
	float spotLightPos[3] = { 0,5,0 };
	float spotLightColor[3] = { 1,1,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f,30.0f };

	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f,0.5f };

	float fighterPos[3] = { 1,1.0f,0 };

	//衝突マネージャ
	CollisionManager *collisionManager = nullptr;

#pragma region タイトルシーン
	void TitleInit();
	void TitleUpdate();
	void TitleDraw();

#pragma region ゲームプレイシーン
	void GamePlayInit();
	void GamePlayUpdate();
	void GamePlayDraw();

#pragma region エンドシーン
	void EndInit();
	void EndUpdate();
	void EndDraw();

public:
	GameScene() {};
	void SceneDelete() override
	{
#pragma region 解放処理
		//XAudio2解放
		Audio::xAudio2.Reset();
		//DirectXCommon解放処理
		//スプライトの解放処理
		debugText->deleteSprite();
		delete spriteBG;
		spriteBG = nullptr;
		//modelObj解放処理
		delete objSkydome;
		objSkydome = nullptr;
		delete objGround;
		objGround = nullptr;
		delete objFighter;
		objFighter = nullptr;
		delete objSphere;
		objSphere = nullptr;
		//model解放処理
		delete modelSkydome;
		modelSkydome = nullptr;
		delete modelGround;
		modelGround = nullptr;
		delete modelFighter;
		modelFighter = nullptr;
		delete modelSphere;
		modelSphere = nullptr;
		//基底クラス解放処理
		Framework::SceneDelete();
	};

	void staticInit() override;
	void Init() override;
	bool Update() override;
	void Draw() override;
};

