#pragma once
#include "K_Graphics\CameraList.h"
#include "K_Graphics\ShaderList.h"
#include "K_Graphics\TextureList.h"

class CSTList
{
private:
	K_Graphics::CameraList			cList;
	K_Graphics::CameraClass*		cPers;
	K_Graphics::CameraClass*		cOrtho;

	K_Graphics::ShaderList			sList;
	K_Graphics::ShaderClass*		shader;

	K_Graphics::TextureList			tList;

	static CSTList* cstlist;
	CSTList() {}

public:
	//インスタンスを得る
	static CSTList* GetInstance();

	//射影投影カメラを作成
	void CreatePerspectiveCamera(const K_Math::Vector3& position, const K_Math::Vector3& target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar, float fieldOfFar);
	//平行投影カメラを作成
	void CreateOrthoCamera(const K_Math::Vector3 &position, const K_Math::Vector3 &target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar);
	//射影投影カメラのアドレス値を得る
	K_Graphics::CameraClass* GetPerspectoveCamera();
	//平行投影カメラのアドレス値を得る
	K_Graphics::CameraClass* GetOrthoCamera();

	//頂点シェーダーとフラグメントシェーダを読み込んでシェーダーを作成
	void CreateShader(const std::string& vsFileName, const std::string& psFileName);
	//シェーダーのアドレス値を得る
	K_Graphics::ShaderClass* GetShaderClass();

	//テクスチャリストのアドレス値を得る
	K_Graphics::TextureList* GetTextureList();
};