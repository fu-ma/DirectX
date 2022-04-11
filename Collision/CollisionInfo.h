#pragma once

#include <DirectXMath.h>

class ModelObj;
class BaseCollider;

/// <summary>
/// 衝突情報
/// </summary>
struct CollisionInfo
{
public:
	CollisionInfo(ModelObj *modelObj, BaseCollider *collider, const DirectX::XMVECTOR &inter)
	{
		this->modelObj = modelObj;
		this->collider = collider;
		this->inter = inter;
	}

	// 衝突相手のオブジェクト
	ModelObj *modelObj = nullptr;
	// 衝突相手のコライダー
	BaseCollider *collider = nullptr;
	// 衝突点
	DirectX::XMVECTOR inter;
};
