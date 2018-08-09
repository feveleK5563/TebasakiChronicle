#include "Effect.h"

//�R���X�g���N�^
EffectManager::EffectManager(){}

//�f�X�g���N�^
EffectManager::~EffectManager()
{
	AllDeleteEffect();
}

//�G�t�F�N�g�̃f�[�^���i�[����
void EffectManager::CreateEffectData(EffectName effectName, const std::string& texName, const std::string& texPath, AnimationCharaChip* anim, int endTime)
{
	effectData[effectName] = new EffectData();
	effectData[effectName]->texture = CST::LoadAndGetTexture(texName, texPath);
	effectData[effectName]->animChip = anim;
	effectData[effectName]->endTime = endTime;
}

//�w����W�Ɏw�肵���G�t�F�N�g�𐶐�����
void EffectManager::CreateEffect(EffectName effectName, const K_Math::Vector3& setPos, int direction)
{
	effectObj.emplace_back(new EffectObject());
	effectObj.back()->imageManager = new ImageManager(effectData[effectName]->texture, true);
	effectObj.back()->imageManager->CreateCharaChip(effectData[effectName]->animChip->chip, effectData[effectName]->animChip->chipSheetNum, effectData[effectName]->animChip->animSpd, effectData[effectName]->animChip->isAnimRoop);
	effectObj.back()->pos = setPos;
	effectObj.back()->timeCnt.SetEndTime(effectData[effectName]->endTime);
	effectObj.back()->direction = direction;
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
	effectObj.shrink_to_fit();
}

//�G�t�F�N�g�̕`��
void EffectManager::Render()
{
	for (auto it : effectObj)
	{
		it->imageManager->ImageDraw3D(it->pos, K_Math::Vector3(0, 0, 0), K_Math::Vector3(1, 1, 1), it->direction);
	}
}

//�S�ẴG�t�F�N�g���폜����
void EffectManager::AllDeleteEffect()
{
	for (auto it : effectData)
	{
		CST::DeleteTexture(it.second->texName);
		Memory::SafeDelete(it.second->animChip);
		delete it.second;
	}
	effectData.clear();

	for (auto it : effectObj)
	{
		delete it->imageManager;
		delete it;
	}
	effectObj.clear();
	effectObj.shrink_to_fit();
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
	//�G�t�F�N�g�̃f�[�^���쐬���A�i�[����
	void CreateEffectData(EffectName effectName, const std::string& texName, const std::string& texPath, AnimationCharaChip* anim)
	{
		effectManager->CreateEffectData(effectName, texName, texPath, anim, int(anim->chipSheetNum * anim->animSpd));
	}

	//�w����W�Ɏw�肵���G�t�F�N�g�𐶐�����
	void CreateEffect(EffectName effectName, const K_Math::Vector3& setPos, int direction)
	{
		effectManager->CreateEffect(effectName, setPos, direction);
	}

	//�G�t�F�N�g�̍X�V����
	void Run()
	{
		effectManager->Run();
	}

	//�G�t�F�N�g�̕`�揈��
	void Render()
	{
		effectManager->Render();
	}

	//�S�ẴG�t�F�N�g�Ƃ��̃f�[�^���폜����
	void AllDeleteEffect()
	{
		effectManager->AllDeleteEffect();
	}
}