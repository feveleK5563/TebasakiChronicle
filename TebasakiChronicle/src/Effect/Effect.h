#pragma once
#include "../BaseClass/ImageManager/ImageManager.h"
#include "../TimeCount.h"

class EffectManager
{
private:
	//エフェクト発生に必要なデータ
	struct EffectData
	{
		AnimationCharaChip	effectAnimData;
		std::string			textureName;
	};
	std::vector<EffectData*> effectData;

	//エフェクトの実体
	struct Effect
	{
		ImageManager		imageManager;
		K_Math::Vector3		pos;
		TimeCount			timeCnt;
	};
	std::vector<Effect*> effect;

public:

};