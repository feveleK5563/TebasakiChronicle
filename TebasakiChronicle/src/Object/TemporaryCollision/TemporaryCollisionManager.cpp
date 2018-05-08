#include "TemporaryCollisionManager.h"

//コリジョンの形状情報を管理させない
TemporaryCollisionManager::TemporaryCollisionManager() : cShape(nullptr) {}

//コリジョンの形状情報を管理させる
TemporaryCollisionManager::TemporaryCollisionManager(K_Physics::CollisionShape* shape) : cShape(shape) {}

//デストラクタ
TemporaryCollisionManager::~TemporaryCollisionManager()
{
	if (cShape != nullptr)
	{
		CC::RemoveCollisionShape(&cShape);
	}
	for (auto it : tempCollision)
	{
		delete it;
	}
}

//-----------------------------------------------------------------------------
//コリジョンを生成する
void TemporaryCollisionManager::CreateTemporaryCollision(
	K_Physics::CollisionShape*	shape,
	CollisionMask&				mmask,
	CollisionMask&				gmask,
	K_Math::Vector3&			setpos,
	K_Math::Vector3&			movevec,
	Status::Direction&			dir,
	int							damage,
	int							deletetime,
	bool						ishitground,
	bool						doground)
{
	tempCollision.emplace_back(new TemporaryCollision(shape, mmask, gmask, setpos, movevec, dir, damage, deletetime, ishitground, doground));
}

//-----------------------------------------------------------------------------
//マネージャの保有するコリジョン形状情報からコリジョンを生成する
void TemporaryCollisionManager::CreateTempCollisionUseSelfShape(
	CollisionMask&				mmask,
	CollisionMask&				gmask,
	K_Math::Vector3&			setpos,
	K_Math::Vector3&			movevec,
	Status::Direction&			dir,
	int							damage,
	int							deletetime,
	bool						ishitground,
	bool						doground)
{
	K_Physics::CollisionData* basecd;
	if (doground == true)
	{
		basecd = CC::CreateCollisionObject(cShape, false, CollisionMask::Non, CollisionMask::Ground);
	}
	else
	{
		basecd = CC::CreateCollisionObject(cShape, true, CollisionMask::Ground, CollisionMask::Non);
	}
	tempCollision.emplace_back(new TemporaryCollision(	basecd,
														CC::CreateCollisionObject(cShape, true, mmask, gmask),
														setpos,
														movevec,
														dir,
														damage,
														deletetime,
														ishitground));
}

//-----------------------------------------------------------------------------
//生成したコリジョンにテクスチャを設定する
void TemporaryCollisionManager::SetAnimationCharaChip(
	std::string&			texName,
	K_Graphics::Texture*	texture,
	K_Math::Box2D&			src,
	int						sheet,
	float					spd,
	bool					isroop)
{
	tempCollision.back()->SetImageManagerAndCharaChip(texName, texture, src, sheet, spd, isroop);
}

//-----------------------------------------------------------------------------
//コリジョンの更新を行う
//コリジョンから消滅要請があった場合消滅させる
void TemporaryCollisionManager::Update()
{
	for (auto it = tempCollision.begin(); it != tempCollision.end();)
	{
		if ((*it)->Update())
		{
			delete (*it);
			tempCollision.erase(it);
		}
		else
		{
			++it;
		}
	}
}

//-----------------------------------------------------------------------------
//コリジョンの描画を行う
void TemporaryCollisionManager::Render()
{
	for (auto it : tempCollision)
	{
		it->Render();
	}
}