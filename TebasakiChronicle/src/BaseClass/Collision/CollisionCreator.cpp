#include "CollisionCreator.h"

CollisionCreator* CollisionCreator::cCreator = nullptr;
//-------------------------------------------------------------------
//インスタンスを得る
CollisionCreator* CollisionCreator::GetInstance()
{
	if (cCreator == nullptr)
		cCreator = new CollisionCreator();

	return cCreator;
}
//-------------------------------------------------------------------
//解放する
void CollisionCreator::Destroy()
{
	delete cCreator;
}

CollisionCreator* cc = CollisionCreator::GetInstance();

namespace CC
{
	//終了処理
	void Delete()
	{
		if (cc != nullptr)
		{
			cc->Destroy();
			cc = nullptr;
		}
	}

	//初期化処理
	void Initialize()
	{
		if (cc->bPhysics == nullptr)
		{
			cc->bPhysics = new K_Physics::BulletPhysics();
			return;
		}
		cc->bPhysics->Initialize();
	}

	//球の形状を作成し、アドレス値を得る
	K_Physics::CollisionShape* CreateSphereShape(float radius)
	{
		return cc->bPhysics->CreateSphereShape(radius);
	}
	//カプセルの形状を作成し、アドレス値を得る
	K_Physics::CollisionShape* CreateCapsuleShape(float radius, float height)
	{
		return cc->bPhysics->CreateCapsuleShape(radius, height);
	}
	//直方体の形状を作成し、アドレス値を得る
	K_Physics::CollisionShape* CreateBoxShape(float halfWidth, float halfHeight, float halfDepth)
	{
		return cc->bPhysics->CreateBoxShape(halfWidth, halfHeight, halfDepth);
	}

	//コリジョンオブジェクトを作成し、アドレス値を得る
	K_Physics::CollisionData* CreateCollisionObject(btCollisionShape* shape, bool ghost, int mask, const K_Math::Vector3 &pos, const K_Math::Vector3 &rot)
	{
		return cc->bPhysics->CreateCollisionObject(shape, ghost, mask, pos, rot);
	}

	//物理世界を更新し、座標を変更する(フレームの最初に呼ぶ)
	void Run()
	{
		cc->bPhysics->Run();
	}

	//コリジョンの移動と当たり判定(正確&重い)
	void MoveCharacter(K_Physics::CollisionData* obj, const K_Math::Vector3 &move, float vLimitAngle, float hLimitAngle)
	{
		cc->bPhysics->MoveCharacter(obj, move, vLimitAngle, hLimitAngle);
	}
	//コリジョンの移動と当たり判定(大雑把&軽い)
	void MoveCharacterDiscrete(K_Physics::CollisionData* obj, const K_Math::Vector3& move, bool vLimitDirection, bool hLimitDirection)
	{
		cc->bPhysics->MoveCharacterDiscrete(obj, move, vLimitDirection, hLimitDirection);
	}
	//衝突のチェック
	std::vector<K_Physics::CollisionTag*>& FindConfrictionObjects(K_Physics::CollisionData *myself)
	{
		return cc->bPhysics->FindConfrictionObjects(myself);
	}

	//コリジョンの描画
	void DebugDraw(K_Graphics::ShaderClass* shaderc, K_Graphics::CameraClass* camerac)
	{
		cc->bPhysics->DebugDraw(shaderc, camerac);
	}
}