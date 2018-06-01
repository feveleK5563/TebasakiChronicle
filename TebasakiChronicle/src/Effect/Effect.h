#pragma once
#include "../BaseClass/ImageManager/ImageManager.h"
#include "../TimeCount.h"

class EffectManager
{
private:
	//�G�t�F�N�g�����ɕK�v�ȃf�[�^
	struct EffectData
	{
		AnimationCharaChip	effectAnimData;
		std::string			textureName;
	};
	std::vector<EffectData*> effectData;

	//�G�t�F�N�g�̎���
	struct Effect
	{
		ImageManager		imageManager;
		K_Math::Vector3		pos;
		TimeCount			timeCnt;
	};
	std::vector<Effect*> effect;

public:

};