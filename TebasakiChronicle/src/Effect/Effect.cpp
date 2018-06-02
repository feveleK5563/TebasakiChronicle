#include "Effect.h"

//�R���X�g���N�^
EffectManager::EffectManager(){}

//�f�X�g���N�^
EffectManager::~EffectManager()
{
	for (auto it : effectData)
	{
		Memory::SafeDelete(it.second->animChip);
		delete it.second;
	}
	for (auto it : effectObj)
	{
		delete it->imageManager;
		delete it;
	}
}

//�G�t�F�N�g�̃f�[�^���쐬���A�i�[����
void EffectManager::CreateEffectData(EffectName effectName, K_Graphics::Texture* tex, AnimationCharaChip* anim, int endTime)
{
	effectData[effectName]->texture = tex;
	effectData[effectName]->animChip = anim;
	effectData[effectName]->endTime = endTime;
}

//�w����W�Ɏw�肵���G�t�F�N�g�𐶐�����
void EffectManager::CreateEffect(EffectName effectName, const K_Math::Vector3& setPos)
{
	effectObj.emplace_back();
	effectObj.back()->imageManager = new ImageManager(effectData[effectName]->texture, false);
	effectObj.back()->imageManager->CreateCharaChip(effectData[effectName]->animChip->chip, effectData[effectName]->animChip->chipSheetNum, effectData[effectName]->animChip->animSpd, effectData[effectName]->animChip->isAnimRoop);
	effectObj.back()->pos = setPos;
	effectObj.back()->timeCnt.SetEndTime(effectData[effectName]->endTime);
}

//�G�t�F�N�g�̍X�V����
void EffectManager::Run()
{
	for (auto it = effectObj.begin(); it != effectObj.end();)
	{
		if ((*it)->timeCnt.IsTimeEnd())
		{
			delete (*it)->imageManager;
			delete (*it);

			it = effectObj.erase(it);
			continue;
		}

		(*it)->imageManager->Animation();
		(*it)->timeCnt.Run();
		++it;
	}
}

//�G�t�F�N�g�̕`��
void EffectManager::Render()
{
	for (auto it : effectObj)
	{
		it->imageManager->ImageDraw3D(it->pos, K_Math::Vector3(0, 0, 0), K_Math::Vector3(1, 1, 1), 0);
	}
}

//�C���X�^���X�𓾂�
EffectManager* EffectManager::GetInstance()
{
	static EffectManager efm;
	return &efm;
}

EffectManager* effectManager = EffectManager::GetInstance();

//�O���ŌĂԊ֐�
namespace Effect
{

}