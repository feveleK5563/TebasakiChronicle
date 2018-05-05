#include "CollisionManager.h"

CollisionManager* CollisionManager::cManager = nullptr;
//-------------------------------------------------------------------
//インスタンスを得る
CollisionManager* CollisionManager::GetInstance()
{
	if (cManager == nullptr)
		cManager = new CollisionManager();

	return cManager;
}
//-------------------------------------------------------------------
//解放する
void CollisionManager::Destroy()
{
	delete cManager;
}

CollisionManager* cm = CollisionManager::GetInstance();

namespace CM
{
	//終了処理
	void Delete()
	{
		if (cm != nullptr)
		{
			cm->Destroy();
			cm = nullptr;
		}
	}

	//初期化(BulletPhysicsを作成)
	void Initialize()
	{
		if (cm->bPhysics == nullptr)
			cm->bPhysics = new K_Physics::BulletPhysics();
	}

	//球の形状を作成し、アドレス値を得る
	K_Physics::CollisionShape* CreateSphereShape(float radius)
	{
		return cm->bPhysics->CreateSphereShape(radius);
	}
	//カプセルの形状を作成し、アドレス値を得る
	K_Physics::CollisionShape* CreateCapsuleShape(float radius, float height)
	{
		return cm->bPhysics->CreateCapsuleShape(radius, height);
	}
	//直方体の形状を作成し、アドレス値を得る
	K_Physics::CollisionShape* CreateBoxShape(float halfWidth, float halfHeight, float halfDepth)
	{
		return cm->bPhysics->CreateBoxShape(halfWidth, halfHeight, halfDepth);
	}

	//コリジョンオブジェクトを作成し、アドレス値を得る
	K_Physics::CollisionData* CreateCollisionObject(btCollisionShape* shape, bool ghost, int mask, const K_Math::Vector3 &pos, const K_Math::Vector3 &rot)
	{
		return cm->bPhysics->CreateCollisionObject(shape, ghost, mask, pos, rot);
	}

	//物理世界を更新し、座標を変更する(フレームの最初に呼ぶ)
	void Run()
	{
		cm->bPhysics->Run();
	}

	//コリジョンの移動と当たり判定(正確&重い)
	void MoveCharacter(K_Physics::CollisionData* obj, const K_Math::Vector3 &move, float vLimitAngle, float hLimitAngle)
	{
		cm->bPhysics->MoveCharacter(obj, move, vLimitAngle, hLimitAngle);
	}
	//コリジョンの移動と当たり判定(大雑把&軽い)
	void MoveCharacterDiscrete(K_Physics::CollisionData* obj, const K_Math::Vector3& move, bool vLimitDirection, bool hLimitDirection)
	{
		cm->bPhysics->MoveCharacterDiscrete(obj, move, vLimitDirection, hLimitDirection);
	}
	//衝突のチェック
	std::vector<K_Physics::CollisionTag*>& FindConfrictionObjects(K_Physics::CollisionData *myself)
	{
		return cm->bPhysics->FindConfrictionObjects(myself);
	}

	//コリジョンの描画
	void DebugDraw(K_Graphics::ShaderClass* sc, K_Graphics::CameraClass* cc)
	{
		cm->bPhysics->DebugDraw(sc, cc);
	}
}