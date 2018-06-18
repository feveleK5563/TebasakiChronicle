#pragma once
#include "MeshModel.h"
#include "../src/CSTList.h"
#include "MapPolygon.h"
#include "../src/BaseClass/Collision/CollisionCreator.h"


//------------------------------------------------------------------------
//�T�v: 3D���f�������[�h���A�`�����o��
//�����:�@�����@�^��
//------------------------------------------------------------------------
class Object3D
{
public:
	//!@brief �R���X�g���N�^
	//!@param[in] filePath ���f���̃p�X
	//!@param[in] texFilePath �e�N�X�`���̃p�X
	//!@param[in] pos_	�ʒu
	//!@param[in] rotation_ ����
	//!@param[in] scale_ �傫��
	Object3D(const std::string& filePath,
		const K_Math::Vector3& pos_,const K_Math::Vector3& rotation_,const K_Math::Vector3& scale_);
	//!@brief �f�X�g���N�^
	~Object3D();

	//!@brief ���f���̃��[�h�ƃe�N�X�`���̃��[�h
	//!@param[in] filePath ���f���̃p�X
	//!@param[in] texName �e�N�X�`���̃p�X
	//!@return �����Ȃ�true
	bool	Load(const std::string& filePath);

	//!@brief �n�`�I�u�W�F�N�g�̐ݒ�
	//!@param[in] decisionPos_ �n�`�̈ʒu
	//!@param[in] decisionAngle_ �n�`�̌���
	//!@param[in] decisionSize_ �n�`�̃T�C�Y
	void	SetDecisionParam(const K_Math::Vector3& decisionPos_,
		const K_Math::Vector3& decisionRotation_,
		const K_Math::Vector3& decisionScale_);

	//!@brief ���f���̕`��
	void	Render();

private:
	//!@brief ���f���f�[�^�����Ƃ�MeshModel�N���X���쐬
	void	CreateMeshModel();
	//!@brief MeshModel�������₷������MeshObject�N���X���쐬
	void	CreateMeshObject();
	//!@brief �n�`�I�u�W�F�N�g�̍쐬
	void	CreateDecisionObj();

private:
	K_Graphics::ModelDataFactory	factory;		//�t�@�N�g��
	K_Graphics::ModelDatas*			modelData;		//���b�V�����f��
	K_Graphics::MeshModel*			model;			//���f���N���X
	K_Graphics::MeshObject*			object;			//MeshModel�������₷������
	K_Physics::MapPolygon*			decisionObj;	//�����蔻��I�u�W�F�N�g
	K_Graphics::TextureList*		texList;		//�e�N�X�`�����X�g
private:
	K_Math::Vector3					decisionPos;		//�����蔻��I�u�W�F�N�g�̈ʒu
	K_Math::Vector3					decisionRotation;	//�����蔻��I�u�W�F�N�g�̉�]
	K_Math::Vector3					decisionScale;		//�����蔻��I�u�W�F�N�g�̃X�P�[��
private:
	std::string						filePath;		//���f���̃t�@�C���p�X
	std::string						texFilePath;	//�e�N�X�`���̃t�@�C���p�X
	std::string						imageName;		//�e�N�X�`����
};