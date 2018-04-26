#include "CSTList.h"

//-------------------------------------------------------------------
//インスタンスを得る
CSTList* CSTList::GetInstance()
{
	static CSTList sl;
	return &sl;
}

//-------------------------------------------------------------------
//射影投影カメラを作成
void CSTList::CreatePerspectiveCamera(const K_Math::Vector3& position, const K_Math::Vector3& target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar, float fieldOfFar)
{
	cList.AddPerspectiveCamera("pers", position, target, screenWidth, screenHeight, cameraNeer, cameraFar, fieldOfFar);
	cPers = cList.GetCamera("pers");
}
//-------------------------------------------------------------------
//平行投影カメラを作成
void CSTList::CreateOrthoCamera(const K_Math::Vector3& position, const K_Math::Vector3& target, int screenWidth, int screenHeight, float cameraNeer, float cameraFar)
{
	cList.AddOrthoCamera("ortho", position, target, screenWidth, screenHeight, cameraNeer, cameraFar);
	cOrtho = cList.GetCamera("ortho");
}
//-------------------------------------------------------------------
//射影投影カメラのアドレス値を得る
K_Graphics::CameraClass* CSTList::GetPerspectoveCamera()
{
	return cPers;
}
//-------------------------------------------------------------------
//平行投影カメラのアドレス値を得る
K_Graphics::CameraClass* CSTList::GetOrthoCamera()
{
	return cOrtho;
}

//-------------------------------------------------------------------
//頂点シェーダーとフラグメントシェーダを読み込んでシェーダーを作成
void CSTList::CreateShader(const std::string& vsFileName, const std::string& psFileName)
{
	sList.LoadVertexShader(vsFileName);
	sList.LoadFragmentShader(psFileName);
	sList.CreateShaderProgram("shader", vsFileName, psFileName);
	shader = sList.GetShader("shader");
}
//-------------------------------------------------------------------
//シェーダーのアドレス値を得る
K_Graphics::ShaderClass* CSTList::GetShaderClass()
{
	return shader;
}

//-------------------------------------------------------------------
//テクスチャリストを取得
K_Graphics::TextureList* CSTList::GetTextureList()
{
	return &tList;
}