#pragma once
#include "CollisionCreator.h"

class CollisionManager
{
private:
	K_Physics::CollisionData*	baseCollision;	//基準となるコリジョン(地形とのめり込み判定のみ行う)

	struct Sub	//サブコリジョン
	{
		K_Physics::CollisionData*	collision;		//サブとなるコリジョン
		K_Math::Vector3*			relativePos;	//ベースコリジョンとの相対座標

		Sub(K_Physics::CollisionData*	cln,
			K_Math::Vector3*			rp) :
			collision(cln),
			relativePos(rp){}
	};
	std::vector<Sub*> subCollision;

	//ベースコリジョンの座標を基にサブコリジョンの位置を設定する
	void SetSubCollisionPos(int angle);

public:
	CollisionManager();
	~CollisionManager();

	//ベースコリジョンを設定する
	//第四引数をfalseで地形との接触判定等を行わない
	void CreateBaseCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool isJudge);

	//サブコリジョンを設定する(指定座標は、オブジェクトが右向き時のベースコリジョンとの相対座標)
	//常にghostはtrue
	void CreateSubCollisionData(K_Physics::CollisionShape* cs, int myselfMask, int giveMask, const K_Math::Vector3& pos, const K_Math::Vector3& rot);

	//指定したサブコリジョンにタグ(userData)を設定する
	void SetSubCollisionTug(int subNum, void* tug);

	//ベースコリジョンを動かし、付随してサブの座標を設定する
	//第三引数をtrueで軽量動作
	void MoveBaseCollision(K_Math::Vector3 moveVec, int angle, bool isLightness);

	//指定したサブコリジョンの受け取ったタグの内、userDataのみを抽出して返す
	//無効(tagIndexが同じ)なコリジョンと衝突した場合は除外する
	std::vector<void*> GetConflictionObjectsUserData(int subNum);
};