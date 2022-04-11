#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

#include "DirectionalLight.h"
#include"PointLight.h"
#include"SpotLight.h"
#include"CircleShadow.h"

/// <summary>
/// ���C�g
/// </summary>
class LightGroup
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �萔
	static const int DirLightNum = 3;
	//�_�����̐�
	static const int PointLightNum = 3;
	//�X�|�b�g���C�g�̐�
	static const int SpotLightNum = 3;
	//�ۉe�̐�
	static const int CircleShadowNum = 1;
public: // �T�u�N���X

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		// �����̐F
		XMFLOAT3 ambientColor;
		float pad1;
		// ���s�����p
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//�_����
		PointLight::ConstBufferData pointLights[PointLightNum];
		//�X�|�b�g���C�g�p
		SpotLight::ConstBufferData spotLights[SpotLightNum];
		//�ۉe�p
		CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
	};

public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device *device);

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static LightGroup *Create();

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device *device;

public: // �����o�֐�

	void SetPointLightActive(int index, bool active);
	void SetPointLightPos(int index, const XMFLOAT3 &lightpos);
	void SetPointLightColor(int index, const XMFLOAT3 &lightcolor);
	void SetPointLightAtten(int index, const XMFLOAT3 &lightAtten);

	void SetSpotLightActive(int index, bool active);
	void SetSpotLightDir(int index, const XMVECTOR &lightdir);
	void SetSpotLightPos(int index, const XMFLOAT3 &lightpos);
	void SetSpotLightColor(int index, const XMFLOAT3 &lightcolor);
	void SetSpotLightAtten(int index, const XMFLOAT3 &lightAtten);
	void SetSpotLightFactorAngle(int index, const XMFLOAT2 &lightFactorAngle);

	void SetCircleShadowActive(int index, bool active);
	void SetCircleShadowCasterPos(int index, const XMFLOAT3 &casterPos);
	void SetCircleShadowDir(int index, const XMVECTOR &lightdir);
	void SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight);
	void SetCircleShadowAtten(int index, const XMFLOAT3 &lightAtten);
	void SetCircleShadowFactorAngle(int index, const XMFLOAT2 &lightFactorAngle);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList *cmdList, UINT rootParameterIndex);

	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// �W���̃��C�g�ݒ�
	/// </summary>
	void DefaultLightSetting();

	/// <summary>
	/// �����̃��C�g�F���Z�b�g
	/// </summary>
	/// <param name="color">���C�g�F</param>
	void SetAmbientColor(const XMFLOAT3 &color);

	/// <summary>
	/// ���s�����̗L���t���O���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="active">�L���t���O</param>
	void SetDirLightActive(int index, bool active);

	/// <summary>
	/// ���s�����̃��C�g�������Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightdir">���C�g����</param>
	void SetDirLightDir(int index, const XMVECTOR &lightdir);

	/// <summary>
	/// ���s�����̃��C�g�F���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightcolor">���C�g�F</param>
	void SetDirLightColor(int index, const XMFLOAT3 &lightcolor);

private: // �����o�ϐ�
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;

	// �����̐F
	XMFLOAT3 ambientColor = { 1,1,1 };

	// ���s�����̔z��
	DirectionalLight dirLights[DirLightNum];

	//�_�����̔z��
	PointLight pointLights[PointLightNum];

	//�X�|�b�g���C�g�̔z��
	SpotLight spotLights[SpotLightNum];

	//�ۉe�̔z�u
	CircleShadow circleShadows[CircleShadowNum];

	// �_�[�e�B�t���O
	bool dirty = false;
};