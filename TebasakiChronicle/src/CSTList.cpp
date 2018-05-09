#include "CSTList.h"

//コンストラクタ
CSTList::CSTList() :
	fList(nullptr)
{
	for (int i = 0; i < 2; ++i)
	{
		cPers[i] = nullptr;
		cOrtho[i] = nullptr;
	}
}

//デストラクタ
CSTList::~CSTList()
{
	if (fList != nullptr)
		delete fList;
}

//-------------------------------------------------------------------
//インスタンスを得る
CSTList* CSTList::GetInstance()
{
	static CSTList cstList;
	return &cstList;
}

CSTList* cstl = CSTList::GetInstance();

//外部で呼ぶ関数
namespace CST
{
	/*☆カメラ関連☆*/

	//-------------------------------------------------------------------
	//射影投影カメラを作成
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
	//平行投影カメラを作成
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
	//射影投影カメラのアドレス値を得る
	K_Graphics::CameraClass* GetPerspectiveCamera(int cameraNum)
	{
		return cstl->cPers[cameraNum];
	}
	//-------------------------------------------------------------------
	//平行投影カメラのアドレス値を得る
	K_Graphics::CameraClass* GetOrthoCamera(int cameraNum)
	{
		return cstl->cOrtho[cameraNum];
	}

	/*☆シェーダー関連☆*/

	//-------------------------------------------------------------------
	//頂点シェーダーとフラグメントシェーダを読み込んでシェーダーを作成
	void CreateShader(const std::string& vsFileName, const std::string& psFileName)
	{
		int size = (int)cstl->shader.size();

		cstl->sList.LoadVertexShader(vsFileName);
		cstl->sList.LoadFragmentShader(psFileName);
		cstl->sList.CreateShaderProgram("shader" + std::to_string(size), vsFileName, psFileName);
		cstl->shader.emplace_back(cstl->sList.GetShader("shader" + std::to_string(size)));
	}
	//-------------------------------------------------------------------
	//シェーダーのアドレス値を得る
	K_Graphics::ShaderClass* GetShaderClass(int shaderNum)
	{
		return cstl->shader[shaderNum];
	}

	/*テクスチャ関連*/

	//-------------------------------------------------------------------
	//テクスチャリストのアドレス値を得る
	K_Graphics::Texture* LoadAndGetTexture(std::string imageName, std::string fileName)
	{
		cstl->tList.LoadTexture(imageName, fileName);

		return cstl->tList.GetTexture(imageName);
	}
	//-------------------------------------------------------------------
	//テクスチャのアドレス値を得る
	K_Graphics::Texture* GetTexture(std::string imageName)
	{
		return cstl->tList.GetTexture(imageName);
	}
	//-------------------------------------------------------------------
	//テクスチャを解放する
	void DeleteTexture(std::string imageName)
	{
		cstl->tList.DeleteTexture(imageName);
	}

	/*フレームバッファ関連*/

	//-------------------------------------------------------------------
	//フレームバッファリストを作成
	void CreateFrameBuffer()
	{
		cstl->fList = new K_Graphics::FrameBufferList(&cstl->tList);
	}

	//-------------------------------------------------------------------
	//指定色でフレームバッファをクリア
	void FrameBufferBeginDraw(int viewPortWidth, int viewPortHeight, float r, float g, float b, bool notDeleteDepthStencil)
	{
		cstl->fList->BeginDraw(viewPortWidth, viewPortHeight, r, g, b, notDeleteDepthStencil);
	}
}