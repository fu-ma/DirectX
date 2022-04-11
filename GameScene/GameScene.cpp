#include "GameScene.h"
#include"Collision.h"
#include"SphereCollider.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "SphereCollider.h"
#include "MeshCollider.h"
#include"FbxLoader.h"

void GameScene::TitleInit()
{
	audio->PlayLoadedSound(soundData2, 0.05f);
	objFighter->SetPosition({ 1,1,0 });
	objSphere->SetPosition({ -1,1,0 });
	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);
}

void GameScene::TitleUpdate()
{
#pragma region �X�V����

	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData2);
		SceneNo = static_cast<int>(GameSceneNo::GamePlay);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	objSphere->Update();
}

void GameScene::TitleDraw()
{
#pragma region �`�揈��

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	// �w�i�X�v���C�g�`��
	spriteBG->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	//objSkydome->Draw();
	objGround->Draw();
	objFighter->Draw();
	objSphere->Draw();


	/*���f���`��㏈��*/
	ModelObj::PostDraw();
	// �p�[�e�B�N���̕`��
	//particleMan->Draw(common->GetCmdList().Get());

	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// �f�o�b�O�e�L�X�g�̕`��
	debugText->DrawAll(common->GetCmdList().Get());

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
}

void GameScene::GamePlayInit()
{
	//�����Đ�
	audio->PlayLoadedSound(soundData1, 0.05f);
	//objFighter->SetPosition({ 1,1,0 });
	objFighter->SetPosition(XMFLOAT3(fighterPos));
	objSphere->SetPosition({ -1,1,0 });
	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);
}

void GameScene::GamePlayUpdate()
{
	// �p�[�e�B�N������
	//CreateParticles();
	XMFLOAT3 rot = objSphere->GetRotation();
	rot.y += 1.0f;
	objSphere->SetRotation(rot);
	//objFighter->SetRotation(rot);
	if (input->isKey(DIK_W))
	{
		fighterPos[1] += 0.01f;
	}
	if (input->isKey(DIK_S))
	{
		fighterPos[1] -= 0.01f;
	}

	if (input->isKey(DIK_A))
	{
		fighterPos[0] += 0.01f;
	}
	if (input->isKey(DIK_D))
	{
		fighterPos[0] -= 0.01f;
	}

	{
		/*lightGroup->SetPointLightPos(0, XMFLOAT3(pointLightPos));
		lightGroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
		lightGroup->SetPointLightAtten(0, XMFLOAT3(pointLightAtten));*/
		/*lightGroup->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0],spotLightDir[1] , spotLightDir[2], 0 }));
		lightGroup->SetSpotLightPos(0, XMFLOAT3(spotLightPos));
		lightGroup->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
		lightGroup->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
		lightGroup->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));*/
		lightGroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0],circleShadowDir[1],circleShadowDir[2],0 }));
		lightGroup->SetCircleShadowCasterPos(0, XMFLOAT3({ fighterPos[0],fighterPos[1],fighterPos[2] }));
		lightGroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
		lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

		objFighter->SetPosition(XMFLOAT3({ fighterPos[0],fighterPos[1] ,fighterPos[2] }));
	}

	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::End);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	objSphere->Update();

	Ray ray;
	ray.start = { 10.0f, 0.5f, 0.0f, 1 };
	ray.dir = { 0,-1,0,0 };
	RaycastHit raycastHit;

	if (collisionManager->Raycast(ray, &raycastHit)) {
		DebugText::GetInstance()->SetPos(0, 30);
		DebugText::GetInstance()->Printf("Raycast Hit.");
	}

	//�S�Ă̏Փ˂��`�F�b�N
	collisionManager->CheckAllCollisions();
}

void GameScene::GamePlayDraw()
{
#pragma region �`�揈��

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	// �w�i�X�v���C�g�`��
	spriteBG->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();


	// ���f�������w�肵�ăt�@�C���ǂݍ���
	FbxLoader::GetInstance()->LoadModelFromFile("cube");


	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	objSkydome->Draw();
	objGround->Draw();
	objFighter->Draw();
	objSphere->Draw();


	/*���f���`��㏈��*/
	ModelObj::PostDraw();
	// �p�[�e�B�N���̕`��
	particleMan->Draw(common->GetCmdList().Get());

	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// �f�o�b�O�e�L�X�g�̕`��
	debugText->DrawAll(common->GetCmdList().Get());

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();

}

void GameScene::EndInit()
{
}

void GameScene::EndUpdate()
{
	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::Title);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	objSphere->Update();

}

void GameScene::EndDraw()
{
	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();
}

void GameScene::staticInit()
{
	//���N���X�̏�����
	Framework::staticInit();

	//���C�g����
	lightGroup.reset(LightGroup::Create());
	//3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	ModelObj::SetLightGroup(lightGroup.get());
	//lightGroup->SetDirLightActive(0, false);
	//lightGroup->SetDirLightActive(1, false);
	//lightGroup->SetDirLightActive(2, false);
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetPointLightActive(1, false);
	lightGroup->SetPointLightActive(2, false);
	//lightGroup->SetSpotLightActive(0, true);
	lightGroup->SetCircleShadowActive(0, true);

	pointLightPos[0] = 0.5f;
	pointLightPos[1] = 1.0f;
	pointLightPos[2] = 0.0f;

	//�����ǂݍ���
	soundData1 = audio->SoundLoadWave("Resources/GAMEBGM.wav",true);
	soundData2 = audio->SoundLoadWave("Resources/TITLEBGM.wav",true);
	soundData3 = audio->SoundLoadWave("Resources/SPACESE.wav", false);

	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(1, L"Resources/background.png");
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// ���f���ǂݍ���
	modelSkydome = Model::CreateFromOBJ("skydome", true);
	modelGround = Model::CreateFromOBJ("ground", true);
	modelFighter = Model::CreateFromOBJ("sphere", true);
	modelSphere = Model::CreateFromOBJ("sphere");

	// 3D�I�u�W�F�N�g����
	collisionManager = CollisionManager::GetInstance();
	objFighter = Player::Create(modelFighter);

	objSkydome = ModelObj::Create(modelSkydome);
	objGround = TouchableObject::Create(modelGround);
	objSphere = ModelObj::Create(modelSphere);

	//�R���C�_�[�̒ǉ�
	objSphere->SetCollider(new SphereCollider({},1.0f));

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	ModelObj::SetCamera(camera.get());

	// �p�[�e�B�N���}�l�[�W������
	// �p�[�e�B�N���}�l�[�W��������
	particleMan->SetCamera(camera.get());
}

void GameScene::Init()
{
	//���N���X�̏�����
	Framework::Init();

	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		TitleInit();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		GamePlayInit();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		EndInit();
		break;
	default:
		break;
	}
}

bool GameScene::Update()
{
	//���N���X�̍X�V
	if (Framework::Update() == false)
	{
		return false;
	}

	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		SceneTime = 1;
		TitleUpdate();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		SceneTime = 1;
		GamePlayUpdate();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		SceneTime = 1;
		EndUpdate();
		break;
	default:
		break;
	}

	return true;
}

void GameScene::Draw()
{
#pragma region �`��O����

	common->PreDraw();

	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		TitleDraw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		GamePlayDraw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		EndDraw();
		break;
	default:
		break;
	}

#pragma region �`��㏈��

	common->PostDraw();
}