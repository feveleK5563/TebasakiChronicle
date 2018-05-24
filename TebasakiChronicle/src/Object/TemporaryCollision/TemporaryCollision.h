#pragma once
#include "../../BaseClass/Collision/CollisionManager.h"

//一時的に生成されるコリジョン
//(時間経過で消えたり、単独で動いたりする)
class TemporaryCollision
{
private:
	K_Physics::CollisionShape*	cShape;			//コリジョンの形状
	CollisionManager			colmanager;		//コリジョンデータの管理者
	GameObject		gameObject;			//ステータス、移動や重力の動作、画像管理、SE、easingを内包したやつ
	int				timeCnt;			//時間計測
	int				deleteTime;			//消滅までの時間
	bool			isHitGround;		//これがtrueだと地形に接触したら消滅する

public:
	//コンストラクタ
	//コリジョンの形状情報をdeleteする
	TemporaryCollision(	K_Physics::CollisionShape*	shape,				//コリジョンの形状
						const CollisionMask&		mmask,				//サブコリジョンのぶつかる対象
						const CollisionMask&		gmask,				//サブコリジョン自身を指す(無効の場合はNon)
						const K_Math::Vector3&		setpos,				//座標
						const K_Math::Vector3&		movevec,			//移動量
						const Status::Direction&	dir,				//テクスチャの向き
						const int					damage,				//対象に与えるダメージ量
						const int					deletetime,			//自身を削除するまでの時間
						const bool					ishitground,		//地形に接触したら消滅するフラグ
						const bool					doground );			//ベースコリジョンを地形として扱うフラグ

	//デストラクタ
	~TemporaryCollision();

	//画像管理者を生成し、同時にキャラチップを設定する
	void SetImageManagerAndCharaChip(	const std::string&		texName,
										K_Graphics::Texture*	texture,
										const K_Math::Box2D&	src,
										int						sheet,
										float					spd,
										bool					isroop);

	//更新(消滅する場合はtrueを返す)
	bool Update();

	//消滅フラグを立てる
	bool Extinction();

	//描画
	void Render();
};