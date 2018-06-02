#include "CSTList.h"

//�R���X�g���N�^
CSTList::CSTList() :
	fList(nullptr)
{
	for (int i = 0; i < 2; ++i)
	{
		cPers[i] = nullptr;
		cOrtho[i] = nullptr;
	}
}

//�f�X�g���N�^
CSTList::~CSTList()
{
	if (fList != nullptr)
		delete fList;
}

//-------------------------------------------------------------------
//�C���X�^���X�𓾂�
CSTList* CSTList::GetInstance()
{
	static CSTList cstList;
	return &cstList;
}

CSTList* cstl = CSTList::GetInstance();

//�O���ŌĂԊ֐�
namespace CST
{
	/*���J�����֘A��*/

	//-------------------------------------------------------------------
	//�ˉe���e�J�������쐬
	void CreatePerspectiveCamera(const K_Math::Vector3& position, const K_Math::Vector3& target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar, float fieldOfFar)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (cstl->cPers[i] == nullptr)
			{
				cstl->cList.AddPerspectiveCamera("pers" + std::to_string(i), position, target, screenWidth, screenHeight, cameraNeer, cameraFar, fieldOfFar);
				cstl->cPers[i] = cstl->cList.GetCamera("pers" + std::to_string(i));
			}
		}
	}
	//-------------------------------------------------------------------
	//���s���e�J�������쐬
	void CreateOrthoCamera(const K_Math::Vector3& position, const K_Math::Vector3& target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (cstl->cOrtho[i] == nullptr)
			{
				cstl->cList.AddOrthoCamera("ortho" + std::to_string(i), position, target, screenWidth, screenHeight, cameraNeer, cameraFar);
				cstl->cOrtho[i] = cstl->cList.GetCamera("ortho" + std::to_string(i));
			}
		}
	}
	//-------------------------------------------------------------------
	//�ˉe���e�J�����̃A�h���X�l�𓾂�
	K_Graphics::CameraClass* GetPerspectiveCamera(int cameraNum)
	{
		return cstl->cPers[cameraNum];
	}
	//-------------------------------------------------------------------
	//���s���e�J�����̃A�h���X�l�𓾂�
	K_Graphics::CameraClass* GetOrthoCamera(int cameraNum)
	{
		return cstl->cOrtho[cameraNum];
	}

	/*���V�F�[�_�[�֘A��*/

	//-------------------------------------------------------------------
	//���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_��ǂݍ���ŃV�F�[�_�[���쐬
	void CreateShader(const std::string& vsFileName, const std::string& psFileName)
	{
		int size = (int)cstl->shader.size();

		cstl->sList.LoadVertexShader(vsFileName);
		cstl->sList.LoadFragmentShader(psFileName);
		cstl->sList.CreateShaderProgram("shader" + std::to_string(size), vsFileName, psFileName);
		cstl->shader.emplace_back(cstl->sList.GetShader("shader" + std::to_string(size)));
	}
	//-------------------------------------------------------------------
	//�V�F�[�_�[�̃A�h���X�l�𓾂�
	K_Graphics::ShaderClass* GetShaderClass(int shaderNum)
	{
		return cstl->shader[shaderNum];
	}

	/*�e�N�X�`���֘A*/

	//-------------------------------------------------------------------
	//�e�N�X�`�����쐬���A���̃A�h���X�l�𓾂�
	K_Graphics::Texture* LoadAndGetTexture(std::string textureName, std::string filePath)
	{
		cstl->tList.LoadTexture(textureName, filePath);

		return cstl->tList.GetTexture(textureName);
	}
	//-------------------------------------------------------------------
	//�e�N�X�`���̃A�h���X�l�𓾂�
	K_Graphics::Texture* GetTexture(std::string textureName)
	{
		return cstl->tList.GetTexture(textureName);
	}
	//-------------------------------------------------------------------
	//�e�N�X�`�����������
	void DeleteTexture(std::string textureName)
	{
		cstl->tList.DeleteTexture(textureName);
	}

	/*�t���[���o�b�t�@�֘A*/

	//-------------------------------------------------------------------
	//�t���[���o�b�t�@���X�g���쐬
	void CreateFrameBuffer()
	{
		cstl->fList = new K_Graphics::FrameBufferList(&cstl->tList);
	}

	//-------------------------------------------------------------------
	//�w��F�Ńt���[���o�b�t�@���N���A
	void FrameBufferBeginDraw(int viewPortWidth, int viewPortHeight, float r, float g, float b, bool notDeleteDepthStencil)
	{
		cstl->fList->BeginDraw(viewPortWidth, viewPortHeight, r, g, b, notDeleteDepthStencil);
	}
}