#include "CSTList.h"
#include "BaseClass/Collision/CollisionCreator.h"
#include "MeshModel.h"
#include "SystemClass.h"
#include "Effect/Effect.h"
#include "BaseClass/Input/Input.h"
#include "MapPolygon.h"
#include "Helper.h"
#include "Scene/SceneManager.h"

#include <cstdio>
#include <cstdlib>
#include <crtdbg.h>
#include <new>
#include <memory>

//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__)xpand(p, s)		_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)

int main()
{
	//���������[�N���m����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(99679);

	//�E�B���h�E
	K_System::SystemClass* sc = new K_System::SystemClass("TebasakiChronicle", Define::ScreenWidth, Define::ScreenHeight, false);

	//CollisionManager��������
	CC::Initialize();

	//�J�������X�g
	K_Math::Vector3 position = K_Math::Vector3(0, 0, -330);
	K_Math::Vector3 target = K_Math::Vector3(0, 0, 0);

	float clipNear = 0.1f;
	float clipFar = 1500.f;
	float fieldOfView = 45.f;
	CST::CreatePerspectiveCamera(position, target, Define::ScreenWidth, Define::ScreenHeight, clipNear, clipFar, fieldOfView);
	CST::CreateOrthoCamera(position, target, Define::ScreenWidth, Define::ScreenHeight, clipNear, clipFar);
	
	INPUT::SetInputClass(sc->GetInput());
	INPUT::Create(K_Input::VpadIndex::Pad0);

	//�V�F�[�_�[���X�g
	CST::CreateShader("data/shader/SpriteShader.vs", "data/shader/SpriteShader.ps");
	CST::CreateShader("data/shader/SimpleShader.vs", "data/shader/SimpleShader.ps");
	CST::CreateShader("data/shader/VertexShader.vs", "data/shader/TextureSampler.ps");

	//�V�[���Ǘ�
	SceneManager* sceneManager = new SceneManager(SceneName::Title);

	//******************************************************************

	while (sc->IsSystemEnd() == false)
	{
		//---------------------------------------------
		//�X�V
		sc->ProcessSystem();
		CC::Run();

		sceneManager->Update();

		//---------------------------------------------
		//�`��
		CST::FrameBufferBeginDraw(Define::ScreenWidth, Define::ScreenHeight, 0.f, 0.f, 1.f);
		CST::GetPerspectiveCamera()->Draw();
		CST::GetOrthoCamera()->Draw();
		
		sceneManager->Draw();

		CC::DebugDraw(CST::GetShaderClass(1), CST::GetPerspectiveCamera());
	
		sc->SwapBuffer();
	}

	delete sc;
	delete sceneManager;
	CC::Delete();
}