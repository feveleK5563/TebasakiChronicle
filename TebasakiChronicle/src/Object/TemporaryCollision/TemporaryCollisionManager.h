#pragma once
#include "TemporaryCollision.h"

//一時的に生成されるコリジョンを管理する
class TemporaryCollisionManager
{
private:
	std::vector<TemporaryCollision*>	tempCollision;	//一時的に生成されるコリジョン

public:
	TemporaryCollisionManager();
	TemporaryCollisionManager(K_Physics::CollisionShape* cshape);
	~TemporaryCollisionManager();

	//コリジョンを生成する
	void CreateTemporaryCollision(	K_Physics::CollisionShape*	shape,			//コリジョンの形状
									const CollisionMask&		mmask,			//ぶつかる対象
									const CollisionMask&		gmask,			//サブコリジョン自身を指す(無効の場合はNon)
									const K_Math::Vector3&		setpos,			//座標
									const K_Math::Vector3&		movevec,		//移動量
									const Status::Direction&	dir,			//テクスチャの向き
									const int					damage,			//対象に与えるダメージ量
									const int					deletetime,		//自身を削除するまでの時間
									const float					gravitySize,	//重力量(0で無効)
									const bool					ishitground,	//地形に接触したら消滅するフラグ
									const bool					doground);		//ベースコリジョンを地形として扱うフラグ

	//生成したコリジョンにテクスチャを設定する
	void SetAnimationCharaChip(	K_Graphics::Texture*	texture,
								const K_Math::Box2D&	src,
								int						sheet,
								float					spd,
								bool					isroop);

	//コリジョンの更新を行う
	//コリジョンから消滅要請があった場合消滅させる
	void Update();

	//コリジョンの描画を行う
	void Render();
};