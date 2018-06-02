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
	//カメラの管理
	K_Graphics::CameraList			cList;
	K_Graphics::CameraClass*		cPers[2];
	K_Graphics::CameraClass*		cOrtho[2];

	//シェーダーの管理
	K_Graphics::ShaderList						sList;
	std::vector<K_Graphics::ShaderClass*>		shader;

	//テクスチャの管理
	K_Graphics::TextureList			tList;

	//フレームバッファの管理
	K_Graphics::FrameBufferList*	fList;

	//インスタンスを得る
	static CSTList* GetInstance();
};

//関数群
namespace CST
{
	//射影投影カメラを作成
	void CreatePerspectiveCamera(const K_Math::Vector3& position, const K_Math::Vector3& target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar, float fieldOfFar);
	//平行投影カメラを作成
	void CreateOrthoCamera(const K_Math::Vector3 &position, const K_Math::Vector3 &target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar);
	//射影投影カメラのアドレス値を得る
	K_Graphics::CameraClass* GetPerspectiveCamera(int cameraNum = 0);
	//平行投影カメラのアドレス値を得る
	K_Graphics::CameraClass* GetOrthoCamera(int cameraNum = 0);

	//頂点シェーダーとフラグメントシェーダを読み込んでシェーダーを作成
	void CreateShader(const std::string& vsFileName, const std::string& psFileName);
	//シェーダーのアドレス値を得る
	K_Graphics::ShaderClass* GetShaderClass(int shaderNum = 0);

	//テクスチャを作成し、そのアドレス値を得る
	K_Graphics::Texture* LoadAndGetTexture(std::string textureName, std::string filePath);
	//テクスチャのアドレス値を得る
	K_Graphics::Texture* GetTexture(std::string textureName);
	//テクスチャを解放する
	void DeleteTexture(std::string textureName);

	//フレームバッファリストを作成
	void CreateFrameBuffer();
	//指定色でフレームバッファをクリア
	void FrameBufferBeginDraw(int viewPortWidth, int viewPortHeight, float r, float g, float b, bool notDeleteDepthStencil = false);
}