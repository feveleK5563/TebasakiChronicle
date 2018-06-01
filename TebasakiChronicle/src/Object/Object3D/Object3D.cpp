#include "Object3D.h"
#include "../src/BaseClass/Collision/CollisionManager.h"

//!@brief �R���X�g���N�^
//!@param[in] filePath ���f���̃p�X
//!@param[in] texName �e�N�X�`���̃p�X
Object3D::Object3D(const std::string& filePath_, const std::string& texFilePath_,
	const K_Math::Vector3& pos_, const K_Math::Vector3& rotation_, const K_Math::Vector3& scale_)
	: modelData(nullptr), model(nullptr), object(nullptr), decisionObj(nullptr),
	texList(new K_Graphics::TextureList()),
	decisionPos(pos_), decisionRotation(rotation_), decisionScale(scale_),
	filePath(filePath_), texFilePath(texFilePath_)
{
	Load(filePath, texFilePath);
	CreateMeshModel();
	CreateMeshObject();
	CreateDecisionObj();
	SetDecisionParam(decisionPos, decisionRotation, decisionScale);
}

//!@brief �f�X�g���N�^
Object3D::~Object3D()
{
	if (model != nullptr)
	{
		delete model;
		model = nullptr;
	}
}

//!@brief ���f���̃��[�h�ƃe�N�X�`���̃��[�h
//!@param[in] filePath ���f���̃p�X
//!@param[in] texName �e�N�X�`���̃p�X
//!@return �����Ȃ�true
bool	Object3D::Load(const std::string& filePath, const std::string& texFilePath)
{
	//�e�N�X�`���̓ǂݍ���
	if (!texList->LoadTexture("fbxTex", texFilePath))
	{
		return false;
	}
	//���f���̓ǂݍ���
	modelData = factory.LoadFBXModel(filePath, texList);
	return true;
}

//!@brief �n�`�I�u�W�F�N�g�̃p�����[�^�ݒ�
//!@param[in] decisionPos_ �n�`�̈ʒu
//!@param[in] decisionAngle_ �n�`�̌���
//!@param[in] decisionSize_ �n�`�̃T�C�Y
void	Object3D::SetDecisionParam(const K_Math::Vector3& decisionPos_,
	const K_Math::Vector3& decisionRotation_,
	const K_Math::Vector3& decisionScale_)
{
	decisionPos = decisionPos_;
	decisionRotation = decisionRotation_;
	decisionScale = decisionScale_;
	decisionObj->GetRigidBody()->SetCollisionPosition(decisionPos);
	decisionObj->GetRigidBody()->SetCollisionRotation(decisionRotation);
	decisionObj->SetScaling(decisionScale);
}

//!@brief ���f���̕`��
void	Object3D::Render()
{
	object->Draw(CST::GetPerspectiveCamera(), CST::GetShaderClass(2),
		decisionPos,
		decisionRotation,
		decisionScale);
}

//!@brief ���f���f�[�^�����Ƃ�MeshModel�N���X���쐬
void	Object3D::CreateMeshModel()
{
	model = new K_Graphics::MeshModel(modelData);
}
//!@brief MeshModel�������₷������MeshObject�N���X���쐬
void	Object3D::CreateMeshObject()
{
	object = new K_Graphics::MeshObject(model);
}

//!@brief �n�`�I�u�W�F�N�g�̍쐬
void	Object3D::CreateDecisionObj()
{
	decisionObj = new K_Physics::MapPolygon(filePath.c_str(), CC::GetBulletPhysics(),
		CollisionMask::Non, CollisionMask::Ground);
}

