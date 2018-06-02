#pragma once
#include "K_Graphics\CameraList.h"
#include "K_Graphics\ShaderList.h"
#include "K_Graphics\TextureList.h"
#include "FrameBufferList.h"

class CSTList
{
private:
	CSTList();
	~CSTList();

public:
	//�J�����̊Ǘ�
	K_Graphics::CameraList			cList;
	K_Graphics::CameraClass*		cPers[2];
	K_Graphics::CameraClass*		cOrtho[2];

	//�V�F�[�_�[�̊Ǘ�
	K_Graphics::ShaderList						sList;
	std::vector<K_Graphics::ShaderClass*>		shader;

	//�e�N�X�`���̊Ǘ�
	K_Graphics::TextureList			tList;

	//�t���[���o�b�t�@�̊Ǘ�
	K_Graphics::FrameBufferList*	fList;

	//�C���X�^���X�𓾂�
	static CSTList* GetInstance();
};

//�֐��Q
namespace CST
{
	//�ˉe���e�J�������쐬
	void CreatePerspectiveCamera(const K_Math::Vector3& position, const K_Math::Vector3& target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar, float fieldOfFar);
	//���s���e�J�������쐬
	void CreateOrthoCamera(const K_Math::Vector3 &position, const K_Math::Vector3 &target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar);
	//�ˉe���e�J�����̃A�h���X�l�𓾂�
	K_Graphics::CameraClass* GetPerspectiveCamera(int cameraNum = 0);
	//���s���e�J�����̃A�h���X�l�𓾂�
	K_Graphics::CameraClass* GetOrthoCamera(int cameraNum = 0);

	//���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_��ǂݍ���ŃV�F�[�_�[���쐬
	void CreateShader(const std::string& vsFileName, const std::string& psFileName);
	//�V�F�[�_�[�̃A�h���X�l�𓾂�
	K_Graphics::ShaderClass* GetShaderClass(int shaderNum = 0);

	//�e�N�X�`�����쐬���A���̃A�h���X�l�𓾂�
	K_Graphics::Texture* LoadAndGetTexture(std::string textureName, std::string filePath);
	//�e�N�X�`���̃A�h���X�l�𓾂�
	K_Graphics::Texture* GetTexture(std::string textureName);
	//�e�N�X�`�����������
	void DeleteTexture(std::string textureName);

	//�t���[���o�b�t�@���X�g���쐬
	void CreateFrameBuffer();
	//�w��F�Ńt���[���o�b�t�@���N���A
	void FrameBufferBeginDraw(int viewPortWidth, int viewPortHeight, float r, float g, float b, bool notDeleteDepthStencil = false);
}