#pragma once
#include "CollisionCreator.h"
#include "../../Object/GameObject.h"

//maskの設定にはこれを使用
enum CollisionMask
{
	Non					= 0,
	Ground				= 1 << 0,
	PlayerCollision		= 1 << 1,
	EnemyCollision		= 1 << 2,
	TakeDamagePlayer	= 1 << 3,
	TakeDamageEnemy		= 1 << 4,
	CameraGan			= 1 << 5,
	EnemyCamCollision	= 1 << 6,
};

class CollisionManager
{
private:
	K_Physics::CollisionData*	baseCollision;	//基準となるコリジョン(地形とのめり込み判定のみ行う)
	K_Math::Vector3				basePosition;	//基準コリジョンの座標
	struct Sub	//サブコリジョン
	{
		K_Physics::CollisionData*	collision;		//サブとなるコリジョン
		K_Math::Vector3				relativePos;	//ベースコリジョンとの相対座標

		Sub(K_Physics::CollisionData*	cln,
			K_Math::Vector3&			rp) :
			collision(cln),
			relativePos(rp){}
	};
	std::vector<Sub*> subCollision;

	//ベースコリジョンの座標を基にサブコリジョンの位置を設定する
	void SetSubCollisionPos(int angle);

public:
	CollisionManager();
	~CollisionManager();

	//ベースコリジョンを作成する
	//第四引数をfalseで地形との接触判定等を行わない
	void CreateBaseCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool isJudge);
	//ベースコリジョンを設定する
	void SetBaseCollisionData(K_Physics::CollisionData* cd, const K_Math::Vector3& pos);

	//サブコリジョンを作成する(指定座標はオブジェクトが右向き時のベースコリジョンとの相対座標)
	//常にghostはtrue
	void CreateSubCollisionData(K_Physics::CollisionShape* cs, int myselfMask, int giveMask, K_Math::Vector3& pos);
	//サブコリジョンを設定する
	void SetSubCollisionData(K_Physics::CollisionData* cd);

	//指定したサブコリジョンにタグ(userData)を設定する
	void SetSubCollisionTug(int subNum, void* tug);

	//ベースコリジョンを動かし、付随してサブの座標を設定する
	//第三引数をtrueで軽量動作
	void MoveBaseCollision(K_Math::Vector3& moveVec, int direction, bool isLightness);

	//指定したサブコリジョンの受け取ったタグの内、userDataのみを抽出して返す
	//無効(tagIndexが同じ)なコリジョンと衝突した場合は除外する
	std::vector<void*> GetConflictionObjectsUserData(int subNum);

	//ベースコリジョンの座標を返す
	K_Math::Vector3& GetBaseCollisionObjectPosition();
};