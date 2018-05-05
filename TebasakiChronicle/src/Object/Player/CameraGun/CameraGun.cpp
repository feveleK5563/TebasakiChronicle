#include "CameraGun.h"

//---------------------------------------------------------------
//概要:カメラガンの実装
//製作者:日比野
//---------------------------------------------------------------

//-------------------------------------------------
//コンストラクタ
//-------------------------------------------------
CameraGun::CameraGun()
{

}

CameraGun::CameraGun(const K_Math::Vector3& vec)
	: moveVec(vec)
{
	//ステータスの設定
	object.GetStatus()->SetStatusData(
		Status::State::Walk,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Left,
		1.0f,
		1);

	//物理を扱うBulletPhysics
	physics = new K_Physics::BulletPhysics();

	//ボックスの形の生成
	shape = physics->CreateSphereShape(10);

	//生成した[形]でコリジョンや剛体を作成
	//K_Physics::RigidBodyData*	rigid = physics->CreateRigidBody(shape, 1.0f, false, 1);
	collision = physics->CreateCollisionObject(shape, false, 1);

	//コリジョンに情報を持たせる
	collision->tag.tagIndex = 1;
	collision->tag.tagName = "CameraGun";
}

//-------------------------------------------------
//デストラクタ
//-------------------------------------------------
CameraGun::~CameraGun()
{
	if (shape != nullptr) { delete shape; shape = nullptr; }
	if (collision != nullptr) { delete collision; collision = nullptr; }
	if (physics != nullptr) { delete physics; physics = nullptr; }

}


//更新処理
void	CameraGun::UpDate()
{	
	//カメラが有効かどうか
	//if (!active) { return; }

	
	if (HitCheck("Enemy"))
	{
		//追跡処理
		K_Math::Vector3* targetPos = (K_Math::Vector3*)targetTag->userData;
		Chase(*targetPos);
	}
	else
	{
		//移動量をセットする
		object.SetMoveVec(moveVec);
	}

	//カメラガンの移動
	physics->MoveCharacter(collision, object.GetMoveVec());
	object.GetPos() += object.GetMoveVec();

	physics->Run();	//物理動作を走らせる

}



//追尾処理
void	CameraGun::Chase(const K_Math::Vector3& targetPos)
{
	//敵とカメラガンとの距離
	K_Math::Vector3 targetVec = targetPos - object.GetStatus()->GetPos();

	//チェック判定
	if (targetVec.x() == 0 && targetVec.y() == 0)
	{
		//敵との座標はすでにあっている
		return;
	}

	//追尾
	float angle = atan2f(targetVec.y(), targetVec.x());	//角度
	float speed = 3.0f;		//スピード

	object.GetMoveVec().x() = cosf(K_Math::DegToRad(angle)) * speed;
}




//-------------
//仮処理
//-------------
void	CameraGun::Initailize()
{
	//ステータスの設定
	object.GetStatus()->SetStatusData(
		Status::State::Walk,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Left,
		1.0f,
		1);
	
	//動きの初期化
	//動きはデフォルトで生成させる

	//画像の設定
	//使い方は今は不明
	//object.GetImage()->

	//物理を扱うBulletPhysics
	physics = new K_Physics::BulletPhysics();

	//ボックスの形の生成
	shape = physics->CreateSphereShape(10);

	//生成した[形]でコリジョンや剛体を作成
	//K_Physics::RigidBodyData*	rigid = physics->CreateRigidBody(shape, 1.0f, false, 1);
	collision = physics->CreateCollisionObject(shape, false, 1);

	//コリジョンに情報を持たせる
	collision->tag.tagIndex = 1;
	collision->tag.tagName = "CameraGun";

	active = false;
}

void	CameraGun::Render()
{
	if (!active) { return; }
}

//向いている方向に移動
void	CameraGun::MoveDir(const K_Math::Vector3& vec)
{
	moveVec = vec;	//ここでは移動量を渡す
}


//カメラガンとの衝突判定
//指定した「タグの名前」と衝突した場合、true
bool	CameraGun::HitCheck(const std::string& name)
{
	std::vector<K_Physics::CollisionTag*>	tags = physics->FindConfrictionObjects(collision);
	for (auto it = tags.begin(); it != tags.end(); ++it)
	{
		if ((*it)->tagName == name)
		{
			//targetTag->userData = (K_Math::Vector3*)(*it)->userData;
			std::cout << "カメラガンと衝突しました" << std::endl;
			return true;
		}
	}
	return false;
}