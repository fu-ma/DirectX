#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include "FBXModel.h"

class FbxLoader
{
private: //エイリアス
	//std::を省略
	using string = std::string;

public: //定数
	// モデル格納ルートパス
	static const string baseDirectory;
	//静的メンバ変数の実体
	static const std::string baseDirectory;
public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader *GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device">D3D12デバイス</param>
	void Initialize(ID3D12Device *device);

	/// <summary>
	/// ファイルからFBXモデル読み込み
	/// <summary>
	/// <param name="modelName">モデル名</param>
	void LoadModelFromFile(const string &modelName);

	/// <summary>
	/// 再帰的にノード構成を解析
	/// </summary>
	/// <param name="model">読み込み先モデルオブジェクト</param>
	/// <param name="fbxNode">解析対象のノード</param>
	/// <param name="parent">親ノード</param>
	void ParseNodeRecursive(FBXModel *model, FbxNode *fbxNode, Node *parent = nullptr);

	/// 後始末
	/// </summary>
	void Finalize();

private:
	// D3D12デバイス
	ID3D12Device *device = nullptr;
	//FBXマネージャ
	FbxManager *fbxManager = nullptr;
	//FBXインポータ
	FbxImporter *fbxImporter = nullptr;

	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader &obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader &obj) = delete;
};