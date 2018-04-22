#include "SystemClass.h"
#include "MeshModel.h"
#include "FrameBufferList.h"
#include "K_Graphics\CameraList.h"
#include "K_Graphics\ShaderList.h"
#include "K_Graphics\TextureList.h"

#include "BaseClass\ImageManager\ImageManager.h"

int main()
{
	//ウィンドウ
	K_System::SystemClass* sc = new K_System::SystemClass(720, 540, false);

	//カメラリスト
	K_Graphics::CameraList* cList = new K_Graphics::CameraList;
	cList->AddPerspectiveCamera("Camera",
		K_Math::Vector3(0, 0, -150), K_Math::Vector3(0, 0, 0), 720, 540, 0.1f, 1500.f, 45.f);

	//シェーダーリスト
	K_Graphics::ShaderList* sList = new K_Graphics::ShaderList;
	sList->LoadVertexShader("data/shader/SpriteShader.vs");
	sList->LoadFragmentShader("data/shader/SpriteShader.ps");
	sList->CreateShaderProgram("Shader", "data/shader/SpriteShader.vs", "data/shader/SpriteShader.ps");

	//テクスチャリスト
	K_Graphics::TextureList* tList = new K_Graphics::TextureList;
	K_Graphics::FrameBufferList* frame = new K_Graphics::FrameBufferList(tList);

	//テクスチャ作ってイメージマネージャーに渡す
	tList->LoadTexture("Test", "./data/image/resource2.tga");
	ImageManager im(cList->GetCamera("Camera"),
					sList->GetShader("Shader"),
					tList->GetTexture("Test"));
	im.CreateCharaChip(K_Math::Box2D(0, 0, 32, 48), 6, 8.f, true);


	while (sc->IsSystemEnd() == false)
	{
		sc->ProcessSystem();

		frame->BeginDraw(720, 540, 0.f, 0.f, 1.f);

		cList->GetCamera("Camera")->Draw();

		im.Animation();

		im.ImageDraw(	K_Math::Vector3(0, 0, 0),
						K_Math::Vector3(0, 0, 0),
						K_Math::Vector3(1, 1, 1));

		sc->SwapBuffer();
	}

	delete sc;
	delete cList;
	delete sList;
	delete tList;
	delete frame;
}