#include "CollisionManager.h"

//コンストラクタ
CollisionManager::CollisionManager() :
	baseCollision(nullptr) {}

//デストラクタ
CollisionManager::~CollisionManager()
{
	for (auto it : subCollision)
	{
		delete it->relativePos;
		delete it;
	}
}

//-----------------------------------------------------------------------------
//ベースコリジョンを設定する
void CollisionManager::CreateBaseCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool isJudge)
{
	if (baseCollision != nullptr)
		return;

	if (isJudge == true)
	{
		//地形とのめり込み処理を行う
		baseCollision = CC::CreateCollisionObject(cs, false, 1, 0, pos, rot);
	}
	else
	{
		//処理を行わない
		baseCollision = CC::CreateCollisionObject(cs, false, 1, 0, pos, rot);
	}
}

//-----------------------------------------------------------------------------
//サブコリジョンを設定する
void CollisionManager::CreateSubCollisionData(K_Physics::CollisionShape* cs, int myselfMask, int giveMask, const K_Math::Vector3& pos, const K_Math::Vector3& rot)
{
	if (baseCollision == nullptr)
		return;

	subCollision.emplace_back(	new Sub(CC::CreateCollisionObject(cs, true, myselfMask, giveMask, pos + baseCollision->GetCollisionPosition(), rot),
								new K_Math::Vector3(pos)));
}

//-----------------------------------------------------------------------------
//サブコリジョンのタグを設定する
void CollisionManager::SetSubCollisionTug(int subNum, void* tug)
{
	subCollision[subNum]->collision->tag.userData = tug;
}

//-----------------------------------------------------------------------------
//ベースコリジョンを動かし、付随してサブの座標を設定する
void CollisionManager::MoveBaseCollision(K_Math::Vector3 moveVec, int angle, bool isLightness)
{
	if (isLightness == true)
	{
		//軽い&大雑把
		CC::MoveCharacterDiscrete(baseCollision, moveVec);
	}
	else
	{
		//重い&正確
		CC::MoveCharacter(baseCollision, moveVec);
	}

	//ベースコリジョンを基に各サブコリジョンの位置を設定
	SetSubCollisionPos(angle);
}

//-----------------------------------------------------------------------------
//ベースコリジョンの座標を基にサブコリジョンの位置を設定する
void CollisionManager::SetSubCollisionPos(int angle)
{
	for (auto it : subCollision)
	{
		K_Math::Vector3 setPos = *it->relativePos;

		if (angle == 180)	//向きが左だった場合位置を反転
			setPos.x() *= -1.f;

		it->collision->SetCollisionPosition(setPos + baseCollision->GetCollisionPosition());
	}
}

//-----------------------------------------------------------------------------
//指定したサブコリジョンの受け取ったタグの内、userDataのみを抽出して返す
std::vector<void*> CollisionManager::GetConflictionObjectsUserData(int subNum)
{
	std::vector<void*> userData;
	std::vector<K_Physics::CollisionTag*> fco = CC::FindConfrictionObjects(subCollision[subNum]->collision);
	for (auto it : fco)
	{
		//tagIndexがこのコリジョンと同じ
		if (it->tagIndex == subCollision[subNum]->collision->tag.tagIndex)
		{
			continue;
		}
		userData.emplace_back(it->userData);
	}
	return userData;
}