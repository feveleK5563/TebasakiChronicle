#include "Effect.h"

//コンストラクタ
EffectManager::EffectManager(){}

//デストラクタ
EffectManager::~EffectManager()
{
	AllDeleteEffect();
}

//エフェクトのデータを格納する
void EffectManager::CreateEffectData(EffectName effectName, const std::string& texName, const std::string& texPath, AnimationCharaChip* anim, int endTime)
{
	effectData[effectName] = new EffectData();
	effectData[effectName]->texture = CST::LoadAndGetTexture(texName, texPath);
	effectData[effectName]->animChip = anim;
	effectData[effectName]->endTime = endTime;
}

//指定座標に指定したエフェクトを生成する
void EffectManager::CreateEffect(EffectName effectName, const K_Math::Vector3& setPos, int direction)
{
	effectObj.emplace_back(new EffectObject());
	effectObj.back()->imageManager = new ImageManager(effectData[effectName]->texture, true);
	effectObj.back()->imageManager->CreateCharaChip(effectData[effectName]->animChip->chip, effectData[effectName]->animChip->chipSheetNum, effectData[effectName]->animChip->animSpd, effectData[effectName]->animChip->isAnimRoop);
	effectObj.back()->pos = setPos;
	effectObj.back()->timeCnt.SetEndTime(effectData[effectName]->endTime);
	effectObj.back()->direction = direction;
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
	effectObj.shrink_to_fit();
}

//エフェクトの描画
void EffectManager::Render()
{
	for (auto it : effectObj)
	{
		it->imageManager->ImageDraw3D(it->pos, K_Math::Vector3(0, 0, 0), K_Math::Vector3(1, 1, 1), it->direction);
	}
}

//全てのエフェクトを削除する
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
	//エフェクトのデータを作成し、格納する
	void CreateEffectData(EffectName effectName, const std::string& texName, const std::string& texPath, AnimationCharaChip* anim)
	{
		effectManager->CreateEffectData(effectName, texName, texPath, anim, int(anim->chipSheetNum * anim->animSpd));
	}

	//指定座標に指定したエフェクトを生成する
	void CreateEffect(EffectName effectName, const K_Math::Vector3& setPos, int direction)
	{
		effectManager->CreateEffect(effectName, setPos, direction);
	}

	//エフェクトの更新処理
	void Run()
	{
		effectManager->Run();
	}

	//エフェクトの描画処理
	void Render()
	{
		effectManager->Render();
	}

	//全てのエフェクトとそのデータを削除する
	void AllDeleteEffect()
	{
		effectManager->AllDeleteEffect();
	}
}