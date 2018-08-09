#pragma once
#include <unordered_map>
#include "../BaseClass/ImageManager/ImageManager.h"
#include "../TimeCount.h"
#include "../CSTList.h"
#include "../Helper.h"

enum struct EffectName
{
	Effect1,
	Effect2,

	BossKnockEffect,
	BossBeamEffect1,
	BossBeamEffect2,
};

class EffectManager
{	
private:
	//エフェクト発生に必要なデータ
	struct EffectData
	{
		AnimationCharaChip*		animChip;	//アニメーション管理
		std::string				texName;	//テクスチャ名
		K_Graphics::Texture*	texture;	//テクスチャ
		int						endTime;	//終了時間
	};
	std::unordered_map<EffectName, EffectData*> effectData;

	//エフェクト
	struct EffectObject
	{
		ImageManager*		imageManager;	//画像表示とアニメーション制御くん
		K_Math::Vector3		pos;			//表示座標
		TimeCount			timeCnt;		//消滅までの時間計測
		int					direction;		//表示の向き
	};
	std::vector<EffectObject*> effectObj;

	EffectManager();
	~EffectManager();

public:
	//エフェクトのデータを格納する
	void CreateEffectData(EffectName effectName, const std::string& texName, const std::string& texPath, AnimationCharaChip* anim, int endTime);
	//指定座標に指定したエフェクトを生成する
	void CreateEffect(EffectName effectName, const K_Math::Vector3& setPos, int direction = 0);

	//エフェクトの更新処理
	void Run();

	//エフェクトの描画処理
	void Render();

	//全てのエフェクトとそのデータを削除する
	void AllDeleteEffect();

	//インスタンスを得る
	static EffectManager* GetInstance();
};

namespace Effect
{
	//エフェクトのデータを格納する
	void CreateEffectData(EffectName effectName, const std::string& texName, const std::string& texPath, AnimationCharaChip* anim);

	//指定座標に指定したエフェクトを生成する
	void CreateEffect(EffectName effectName, const K_Math::Vector3& setPos, int direction = 0);

	//エフェクトの更新処理
	void Run();

	//エフェクトの描画処理
	void Render();

	//全てのエフェクトとそのデータを削除する
	void AllDeleteEffect();
}