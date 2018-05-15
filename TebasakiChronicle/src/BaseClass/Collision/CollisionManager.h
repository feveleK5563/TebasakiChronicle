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
	CameraGunCollision	= 1 << 5,
	EnemyCamCollision	= 1 << 6,
};

//コリジョンデータ管理くん
//コリジョンの形状情報は格納しないので各自で管理すること
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
			const K_Math::Vector3&		rp) :
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
	//第四引数をfalseで地形とのめり込み判定を行わない
	void CreateBaseCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool isJudge);
	//ベースコリジョンを設定する
	void SetBaseCollisionData(K_Physics::CollisionData* cd, const K_Math::Vector3& pos);

	//地形として振る舞うベースコリジョンを作成する
	//※特に理由がない限り使用しないこと(第四引数をfalseでめり込み判定なし通常ベースコリジョンを作成する)
	void CreateGroundCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool doGround);

	//サブコリジョンを作成する(指定座標はオブジェクトが右向き時のベースコリジョンとの相対座標)
	//常にghostはtrue
	void CreateSubCollisionData(K_Physics::CollisionShape* cs, int myselfMask, int giveMask, const K_Math::Vector3& pos);
	//サブコリジョンを設定する
	void SetSubCollisionData(K_Physics::CollisionData* cd);

	//指定したサブコリジョンにタグ(TagName)を設定する
	void SetSubCollisionTagName(int subNum, std::string& name);
	//指定したサブコリジョンにタグ(TagIndex)を設定する
	void SetSubCollisionTagIndex(int subNum, int indexNum);
	//指定したサブコリジョンにタグ(UserData)を設定する
	void SetSubCollisionUserData(int subNum, void* data);

	//指定したサブコリジョンのマスクを設定する
	void SetSubCollisionMyselfMask(int subNum, int myselfMask);
	void SetSubCollisionGiveMask(int subNum, int giveMask);
	//指定したサブコリジョンのマスクを調べる
	int GetSubCollisionMyselfMask(int subNum);
	int GetSubCollisionGiveMask(int subNum);

	//ベースコリジョンを動かし、付随してサブの座標を設定する
	//第三引数をtrueで軽量な処理(めり込み判定を行う場合はfalse推奨)
	void MoveBaseCollision(K_Math::Vector3& moveVec, int direction, bool isLightness);

	//指定したサブコリジョンの受け取ったタグを返す
	std::vector<K_Physics::CollisionTag*>& GetConflictionObjectsTag(int subNum);

	//ベースコリジョンが地形コリジョンと衝突していたらtrueを返す
	bool CheckHitBaseCollisionObject();

	//指定したサブコリジョンが他コリジョンと衝突していたらtrueを返す
	bool CheckHitSubCollisionObejct(int subNum);

	//ベースコリジョンの座標を返す
	K_Math::Vector3& GetBaseCollisionObjectPosition();

	//ベースコリジョンの座標を設定する
	void SetBaseCollisionObjectPosition(const K_Math::Vector3& setpos);
};