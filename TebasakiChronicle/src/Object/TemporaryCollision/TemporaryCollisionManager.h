#pragma once
#include "TemporaryCollision.h"

//一時的に生成されるコリジョンを管理する
class TemporaryCollisionManager
{
private:
	K_Physics::CollisionShape*			cShape;			//コリジョンの形状情報(場合によっては使用しない)
	std::vector<TemporaryCollision*>	tempCollision;	//一時的に生成されるコリジョン

public:
	TemporaryCollisionManager();
	TemporaryCollisionManager(K_Physics::CollisionShape* cshape);
	~TemporaryCollisionManager();

	//コリジョンを生成する
	void CreateTemporaryCollision(	K_Physics::CollisionShape*	shape,			//コリジョンの形状
									CollisionMask&				mmask,			//ぶつかる対象
									CollisionMask&				gmask,			//サブコリジョン自身を指す(無効の場合はNon)
									K_Math::Vector3&			setpos,			//座標
									K_Math::Vector3&			movevec,		//移動量
									Status::Direction&			dir,			//テクスチャの向き
									int							damage,			//対象に与えるダメージ量
									int							deletetime,		//自身を削除するまでの時間
									bool						ishitground,	//地形に接触したら消滅するフラグ
									bool						doground);		//ベースコリジョンを地形として扱うフラグ

	//マネージャの保有するコリジョン形状情報からコリジョンを生成する
	void CreateTempCollisionUseSelfShape(	CollisionMask&				mmask,			//ぶつかる対象
											CollisionMask&				gmask,			//サブコリジョン自身を指す(無効の場合はNon)
											K_Math::Vector3&			setpos,			//座標
											K_Math::Vector3&			movevec,		//移動量
											Status::Direction&			dir,			//テクスチャの向き
											int							damage,			//対象に与えるダメージ量
											int							deletetime,		//自身を削除するまでの時間
											bool						ishitground,	//地形に接触したら消滅するフラグ
											bool						doground);		//ベースコリジョンを地形として扱うフラグ

	//生成したコリジョンにテクスチャを設定する
	void SetAnimationCharaChip(	std::string&			texName,
								K_Graphics::Texture*	texture,
								K_Math::Box2D&			src,
								int						sheet,
								float					spd,
								bool					isroop);

	//コリジョンの更新を行う
	//コリジョンから消滅要請があった場合消滅させる
	void Update();

	//コリジョンの描画を行う
	void Render();
};