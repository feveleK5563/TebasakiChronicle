#include "Scene_GameOver.h"

//�R���X�g���N�^
Scene_GameOver::Scene_GameOver()
{
	tex = CST::LoadAndGetTexture("over", "data/image/���Q�[���I�[�o�[.png");
	spobj = new K_Graphics::SpriteObject(tex);
}

//�f�X�g���N�^
Scene_GameOver::~Scene_GameOver()
{
	CST::DeleteTexture("over");
	delete spobj;
}

//�X�V(���ɐݒ肵�����V�[������Ԃ�)
SceneName Scene_GameOver::Update()
{
	SceneName nextScene = SceneName::Non;
	if (INPUT::IsPressButton(VpadIndex::Pad0, K_Input::VpadButton::L1))
	{
		nextScene = SceneName::Title;
	}
	return nextScene;
}

//�`��
void Scene_GameOver::Draw()
{
	CST::GetShaderClass(0)->UseShader();
	spobj->Draw2D(
		CST::GetOrthoCamera(),
		CST::GetShaderClass(0),
		K_Math::Box2D(0, 0, 1280, 720),
		K_Math::Box2D(0, 0, 1280, 720),
		0.f);
}