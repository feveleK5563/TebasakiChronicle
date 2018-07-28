#include "Scene_Title.h"

//コンストラクタ
Scene_Title::Scene_Title()
{
	tex = CST::LoadAndGetTexture("kariTitle", "data/image/仮タイトル.png");
	spobj = new K_Graphics::SpriteObject(tex);
}

//デストラクタ
Scene_Title::~Scene_Title()
{
	CST::DeleteTexture("kariTitle");
	delete spobj;
}

//更新(次に設定したいシーン名を返す)
SceneName Scene_Title::Update()
{
	SceneName nextScene = SceneName::Non;
	if (INPUT::IsPressButton(VpadIndex::Pad0, K_Input::VpadButton::L1))
	{
		nextScene = SceneName::Game;
	}
	return nextScene;
}

//描画
void Scene_Title::Draw()
{
	CST::GetShaderClass(0)->UseShader();
	CST::GetShaderClass(0)->SetValue("color", K_Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	spobj->Draw2D(
		CST::GetOrthoCamera(),
		CST::GetShaderClass(0),
		K_Math::Box2D(0, 0, 1280, 720),
		K_Math::Box2D(0, 0, 1280, 720),
		0.f);
}