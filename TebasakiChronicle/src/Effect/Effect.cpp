#include "Effect.h"

//コンストラクタ
EffectManager::EffectManager(){}

//デストラクタ
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

//エフェクトのデータを作成し、格納する
void EffectManager::CreateEffectData(EffectName effectName, K_Graphics::Texture* tex, AnimationCharaChip* anim, int endTime)
{
	effectData[effectName]->texture = tex;
	effectData[effectName]->animChip = anim;
	effectData[effectName]->endTime = endTime;
}

//指定座標に指定したエフェクトを生成する
void EffectManager::CreateEffect(EffectName effectName, const K_Math::Vector3& setPos)
{
	effectObj.emplace_back();
	effectObj.back()->imageManager = new ImageManager(effectData[effectName]->texture, false);
	effectObj.back()->imageManager->CreateCharaChip(effectData[effectName]->animChip->chip, effectData[effectName]->animChip->chipSheetNum, effectData[effectName]->animChip->animSpd, effectData[effectName]->animChip->isAnimRoop);
	effectObj.back()->pos = setPos;
	effectObj.back()->timeCnt.SetEndTime(effectData[effectName]->endTime);
}

//エフェクトの更新処理
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

//エフェクトの描画
void EffectManager::Render()
{
	for (auto it : effectObj)
	{
		it->imageManager->ImageDraw3D(it->pos, K_Math::Vector3(0, 0, 0), K_Math::Vector3(1, 1, 1), 0);
	}
}

//インスタンスを得る
EffectManager* EffectManager::GetInstance()
{
	static EffectManager efm;
	return &efm;
}

EffectManager* effectManager = EffectManager::GetInstance();

//外部で呼ぶ関数
namespace Effect
{

}