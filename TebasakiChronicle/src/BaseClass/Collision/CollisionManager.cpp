#include "CollisionManager.h"

//コンストラクタ
CollisionManager::CollisionManager() :
	baseCollision(nullptr),
	basePosition(K_Math::Vector3(0, 0, 0)){}

//デストラクタ
CollisionManager::~CollisionManager()
{
	for (auto it : subCollision)
	{
		CC::RemoveCollision(&it->collision);
		delete it;
	}
	CC::RemoveCollision(&baseCollision);
}

//-----------------------------------------------------------------------------
//ベースコリジョンを作成する
void CollisionManager::CreateBaseCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool isJudge)
{
	if (baseCollision != nullptr)
		return;

	if (isJudge == true)
	{
		//地形とのめり込み判定を行うコリジョンを作成
		baseCollision = CC::CreateCollisionObject(cs, false, CollisionMask::Ground, CollisionMask::Non, pos, rot);
	}
	else
	{
		//めり込み判定を行わないコリジョンを作成
		baseCollision = CC::CreateCollisionObject(cs, true, CollisionMask::Ground, CollisionMask::Non, pos, rot);
	}
}
//-----------------------------------------------------------------------------
//ベースコリジョンを設定する
void CollisionManager::SetBaseCollisionData(K_Physics::CollisionData* cd, const K_Math::Vector3& pos)
{
	if (baseCollision != nullptr)
		return;

	baseCollision = cd;
	baseCollision->SetCollisionPosition(pos);
}

//-----------------------------------------------------------------------------
//地形として振る舞うベースコリジョンを作成する
//※特に理由がない限り使用しないこと(第四引数をfalseで通常のベースコリジョンを作成する)
void CollisionManager::CreateGroundCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool doGround)
{
	if (doGround == false)
	{
		CreateBaseCollisionData(cs, pos, rot, false);
		return;
	}

	if (baseCollision != nullptr)
		return;

	//地形として振る舞うコリジョンを作成
	baseCollision = CC::CreateCollisionObject(cs, false, CollisionMask::Non, CollisionMask::Ground, pos, rot);
}


//-----------------------------------------------------------------------------
//サブコリジョンを作成する
void CollisionManager::CreateSubCollisionData(K_Physics::CollisionShape* cs, int myselfMask, int giveMask, const K_Math::Vector3& pos)
{
	if (baseCollision == nullptr)
		return;

	subCollision.emplace_back(new Sub(CC::CreateCollisionObject(cs, true, myselfMask, giveMask, pos + baseCollision->GetCollisionPosition()), pos));
}
//-----------------------------------------------------------------------------
//サブコリジョンを設定する
void CollisionManager::SetSubCollisionData(K_Physics::CollisionData* cd)
{
	if (baseCollision == nullptr)
		return;

	K_Math::Vector3* ccd = &cd->GetCollisionPosition();
	subCollision.emplace_back(new Sub(cd, *ccd));
	subCollision.back()->collision->SetCollisionPosition(*ccd + baseCollision->GetCollisionPosition());
}

//-----------------------------------------------------------------------------
//指定したサブコリジョンにタグ(TagName)を設定する
void CollisionManager::SetSubCollisionTagName(int subNum, std::string& name)
{
	subCollision[subNum]->collision->tag.tagName = name;
}
//-----------------------------------------------------------------------------
//指定したサブコリジョンにタグ(TagIndex)を設定する
void CollisionManager::SetSubCollisionTagIndex(int subNum, int indexNum)
{
	subCollision[subNum]->collision->tag.tagIndex = indexNum;
}
//-----------------------------------------------------------------------------
//指定したサブコリジョンのタグ(UserData)を設定する
void CollisionManager::SetSubCollisionUserData(int subNum, void* data)
{
	subCollision[subNum]->collision->tag.userData = data;
}

//-----------------------------------------------------------------------------
//指定したサブコリジョンのマスクを設定する
void CollisionManager::SetSubCollisionMyselfMask(int subNum, int myselfMask)
{
	subCollision[subNum]->collision->SetMyselfMask(myselfMask);
}
void CollisionManager::SetSubCollisionGiveMask(int subNum, int giveMask)
{
	subCollision[subNum]->collision->SetGiveMask(giveMask);
}
//-----------------------------------------------------------------------------
//指定したサブコリジョンのマスクを調べる
int CollisionManager::GetSubCollisionMyselfMask(int subNum)
{
	return subCollision[subNum]->collision->GetMyselfMask();
}
int CollisionManager::GetSubCollisionGiveMask(int subNum)
{
	return subCollision[subNum]->collision->GetGiveMask();
}

//-----------------------------------------------------------------------------
//ベースコリジョンを動かし、付随してサブの座標を設定する
void CollisionManager::MoveBaseCollision(K_Math::Vector3& moveVec, int direction, bool isLightness)
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
	SetSubCollisionPos(direction);
}

//-----------------------------------------------------------------------------
//ベースコリジョンの座標を基にサブコリジョンの位置を設定する
void CollisionManager::SetSubCollisionPos(int angle)
{
	for (auto it : subCollision)
	{
		K_Math::Vector3 setPos = it->relativePos;

		if (angle == 180)	//向きが左だった場合位置を反転
			setPos.x *= -1.f;

		it->collision->SetCollisionPosition(setPos + baseCollision->GetCollisionPosition());
	}
}

//-----------------------------------------------------------------------------
//指定したサブコリジョンの受け取ったタグを返す
std::vector<K_Physics::CollisionTag*>& CollisionManager::GetConflictionObjectsTag(int subNum)
{
	return CC::FindConfrictionObjects(subCollision[subNum]->collision);
}

//-----------------------------------------------------------------------------
//ベースコリジョンが地形コリジョンと衝突していたらtrueを返す
bool CollisionManager::CheckHitBaseCollisionObject()
{
	return CC::FindConfrictionObjects(baseCollision).size() > 0;
}

//-----------------------------------------------------------------------------
//指定したサブコリジョンが他コリジョンと衝突していたらtrueを返す
bool CollisionManager::CheckHitSubCollisionObejct(int subNum)
{
	return CC::FindConfrictionObjects(subCollision[subNum]->collision).size() > 0;
}

//-----------------------------------------------------------------------------
//ベースコリジョンの座標を返す
K_Math::Vector3& CollisionManager::GetBaseCollisionObjectPosition()
{
	//座標を取得(直接baseCollision->GeteCollisionPositionを返すと寿命が尽きるため)
	basePosition = baseCollision->GetCollisionPosition();

	return basePosition;
}

//-----------------------------------------------------------------------------
//ベースコリジョンの座標を設定する
void CollisionManager::SetBaseCollisionObjectPosition(const K_Math::Vector3& setpos)
{
	baseCollision->SetCollisionPosition(setpos);
}