#pragma once
#include <unordered_map>
#include "../BaseClass/ImageManager/ImageManager.h"
#include "../TimeCount.h"
#include "../CSTList.h"
#include "../Helper.h"

class EffectManager
{
public:
	enum EffectName
	{
		Effect1,
		Effect2,
	};
	
private:
	//エフェクト発生に必要なデータ
	struct EffectData
	{
		AnimationCharaChip*		animChip;	//アニメーション管理
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
	};
	std::vector<EffectObject*> effectObj;

	EffectManager();
	~EffectManager();

public:
	//エフェクトのデータを作成し、格納する
	void CreateEffectData(EffectName effectName, K_Graphics::Texture* tex, AnimationCharaChip* anim, int endTime);
	//指定座標に指定したエフェクトを生成する
	void CreateEffect(EffectName effectName, const K_Math::Vector3& setPos);

	//エフェクトの更新処理
	void Run();

	//エフェクトの描画処理
	void Render();

	//インスタンスを得る
	static EffectManager* GetInstance();
};

namespace Effect
{

}