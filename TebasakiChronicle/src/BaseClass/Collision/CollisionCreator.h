#pragma once
#include "K_Physics\BulletPhysics.h"
#include "K_Graphics\CameraClass.h"
#include "K_Graphics\ShaderClass.h"

class CollisionCreator
{
private:
	static CollisionCreator* cCreator;
	CollisionCreator() : 
		bPhysics(nullptr){}

	~CollisionCreator()
	{
		if (bPhysics != nullptr)
			delete bPhysics;
	}

public:
	K_Physics::BulletPhysics* bPhysics;

	//インスタンスを得る
	static CollisionCreator* GetInstance();
	//解放する
	void Destroy();
};

//関数群
namespace CC
{
	//終了処理
	void Delete();

	//初期化(BulletPhysicsを作成)
	void Initialize();

	//球の形状を作成し、アドレス値を得る
	K_Physics::CollisionShape* CreateSphereShape(float radius);
	//カプセルの形状を作成し、アドレス値を得る
	K_Physics::CollisionShape* CreateCapsuleShape(float radius, float height);
	//直方体の形状を作成し、アドレス値を得る
	K_Physics::CollisionShape* CreateBoxShape(float halfWidth, float halfHeight, float halfDepth);

	//コリジョンオブジェクトを作成し、アドレス値を得る
	K_Physics::CollisionData* CreateCollisionObject(btCollisionShape* shape, bool ghost, int myselfMask, int giveMask, const K_Math::Vector3 &pos = K_Math::Vector3(0, 0, 0), const K_Math::Vector3 &rot = K_Math::Vector3(0, 0, 0));

	//物理世界を更新し、座標を変更する(フレームの最初に呼ぶ)
	void Run();

	//コリジョンの移動と当たり判定(正確&重い)
	void MoveCharacter(K_Physics::CollisionData* obj, const K_Math::Vector3 &move, float vLimitAngle = 40.0f, float hLimitAngle = 0.0f);
	//コリジョンの移動と当たり判定(大雑把&軽い)
	void MoveCharacterDiscrete(K_Physics::CollisionData* obj, const K_Math::Vector3& move, bool vLimitDirection = true, bool hLimitDirection = false);
	//衝突のチェック
	std::vector<K_Physics::CollisionTag*>& FindConfrictionObjects(K_Physics::CollisionData *myself);

	//コリジョンの描画
	void DebugDraw(K_Graphics::ShaderClass* sc, K_Graphics::CameraClass* cc);
}