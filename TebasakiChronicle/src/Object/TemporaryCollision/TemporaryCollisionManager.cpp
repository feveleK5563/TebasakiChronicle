#include "TemporaryCollisionManager.h"

//コリジョンの形状情報を管理させない
TemporaryCollisionManager::TemporaryCollisionManager() {}

//コリジョンの形状情報を管理させる
TemporaryCollisionManager::TemporaryCollisionManager(K_Physics::CollisionShape* shape) {}

//デストラクタ
TemporaryCollisionManager::~TemporaryCollisionManager()
{
	for (auto it : tempCollision)
	{
		delete it;
	}
}

//-----------------------------------------------------------------------------
//コリジョンを生成する
void TemporaryCollisionManager::CreateTemporaryCollision(
	K_Physics::CollisionShape*	shape,
	const CollisionMask&		mmask,
	const CollisionMask&		gmask,
	const K_Math::Vector3&		setpos,
	const K_Math::Vector3&		movevec,
	const Status::Direction&	dir,
	const int					damage,
	const int					deletetime,
	const bool					ishitground,
	const bool					doground)
{
	tempCollision.emplace_back(new TemporaryCollision(shape, mmask, gmask, setpos, movevec, dir, damage, deletetime, ishitground, doground));
}

//-----------------------------------------------------------------------------
//生成したコリジョンにテクスチャを設定する
void TemporaryCollisionManager::SetAnimationCharaChip(
	const std::string&			texName,
	K_Graphics::Texture*		texture,
	const K_Math::Box2D&		src,
	int							sheet,
	float						spd,
	bool						isroop)
{
	tempCollision.back()->SetImageManagerAndCharaChip(texName, texture, src, sheet, spd, isroop);
}

//-----------------------------------------------------------------------------
//コリジョンの更新を行う
//コリジョンから消滅要請があった場合消滅させる
void TemporaryCollisionManager::Update()
{
	auto it = tempCollision.begin();
	for (;it != tempCollision.end();)
	{
		if ((*it)->Update())
		{
			delete (*it);
			it = tempCollision.erase(it);
		}
		else
		{
			++it;
		}
	}
	tempCollision.shrink_to_fit();
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