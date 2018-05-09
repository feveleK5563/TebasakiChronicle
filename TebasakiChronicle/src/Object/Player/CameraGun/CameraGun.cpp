#include "CameraGun.h"

//---------------------------------------------------------------
//概要:カメラガンの実装
//製作者:日比野
//---------------------------------------------------------------

//-------------------------------------------------
//コンストラクタ
//-------------------------------------------------

CameraGun::CameraGun() : 
	targetUserData(nullptr)
{
	//ステータスの設定
	object.GetStatus().SetStatusData(
		Status::State::Non,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Right,
		1,
		1);
	object.GetMove().SetAddVec(3.f);

	//ボックスの形の生成
	shape = CC::CreateBoxShape(10, 10, 1);

	//生成した[形]でコリジョンや剛体を作成
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), false);
	cManager.CreateSubCollisionData(shape, CollisionMask::EnemyCamCollision, CollisionMask::CameraGan, object.GetPos());

	//コリジョンに情報を持たせる
	cManager.SetSubCollisionTug(0, &object.GetStatus());
}

//-------------------------------------------------
//デストラクタ
//-------------------------------------------------
CameraGun::~CameraGun()
{
	CC::RemoveCollisionShape(&shape);
}

//-------------
//初期化処理
//-------------
void	CameraGun::Initailize()
{
	//ステータスの設定
	object.GetStatus().SetStatusData(
		Status::State::Non,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Left,
		1,
		1);

	object.GetMove().SetAddVec(3.0f);

	//動きの初期化
	//動きはデフォルトで生成させる
	object.CreateImg("cameraGun", "./data/image/target.png");
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 353, 352), 1, 1, false);

	//ボックスの形の生成
	shape = CC::CreateBoxShape(10, 10, 1);

	//生成した[形]でコリジョンや剛体を作成
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), false);
	cManager.CreateSubCollisionData(shape, CollisionMask::EnemyCamCollision, CollisionMask::CameraGan, object.GetPos());

	//コリジョンに情報を持たせる
	cManager.SetSubCollisionTug(0, &object.GetState());
}

//-----------------------------------
//更新処理
//-----------------------------------
void	CameraGun::UpDate(const K_Math::Vector3& pPos)
{	
	//カメラが無効のとき
	if (CheckNowState(Status::State::Non))
	{ 
		//プレイヤーに追従する
		SetPlayerPos(pPos);
	}
	else if (CheckNowState(Status::State::Active))
	{
		//カメラガンが有効のとき
		//衝突した際の挙動
		if (!CheckUserData())
		{
			//static_cast<SkillManager>(targetUserData).pos;
			//K_Math::Vector3	tarPos = static_cast<K_Math::Vector3>(targetUserData);
			//Chase(tarPos);
		}
		else
		{
			//衝突していない場合、方向にすすみ続ける
			object.GetPos() += object.GetMoveVec();
			float addSpeed = -GetDir() * 0.02f;
			if (CheckAddSpeed())
			{
				object.GetMoveVec().x() += addSpeed;
			}
		}
	}
	
	//アニメーション処理
	object.GetImage().Animation();

	//カメラガンの移動
	cManager.MoveBaseCollision(object.GetMoveVec(), object.GetDirection(), false);
	//コリジョンの位置の同期
	cManager.GetBaseCollisionObjectPosition() = object.GetPos();
}



//---------------------------------
//描画
//---------------------------------
void	CameraGun::Render()
{
	if (object.GetStatus().GetState() == Status::Non) { return; }
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), 1);
}


//プレイヤーの位置と同期
void	CameraGun::SetPlayerPos(const K_Math::Vector3& pos)
{
	object.GetPos() = pos;
	object.SetMoveVec(K_Math::Vector3(0, 0, 0));
}


//追尾処理
void	CameraGun::Chase(const K_Math::Vector3& targetPos)
{
	//敵とカメラガンとの距離
	K_Math::Vector3 targetVec = targetPos - object.GetPos();

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

//敵との衝突をした場合、スキルデータを取得する
void	CameraGun::RecieveData()
{
	//当たり判定処理
	std::vector<void*> data = cManager.GetConflictionObjectsUserData(0);
	if (data.size() > 0)
	{
		targetUserData = data[0];
	}
}


//ユーザーデータがあるかのチェック
bool	CameraGun::CheckUserData()
{
	if (targetUserData == nullptr)
	{
		return true;
	}
	return false;
}


//ベクトルの設定
void	CameraGun::SetMoveVec(bool isInjection)
{
	if (isInjection)
	{
		object.SetMoveVec(K_Math::Vector3(GetDir() * object.GetMove().GetAddVec(), 0, 0));
	}
	else
	{
		object.SetMoveVec(K_Math::Vector3(0, 0, 0));
	}
}


//向きの設定
void	CameraGun::SetDirection(const Status::Direction& dir)
{
	object.SetDirection(dir);
}

//向きを返す
float	CameraGun::GetDir()
{
	if (object.GetDirection() == Status::Direction::Left)
	{
		return -1.0f;
	}
	else if (object.GetDirection() == Status::Direction::Right)
	{
		return 1.0f;
	}
	return 1.0f;
}


//現在の状態を調べる
bool	CameraGun::CheckNowState(const Status::State& state)
{
	if (object.GetState() == state)
	{
		return true;
	}
	return false;
}

//moveVecが戻らないようにする
//進行方向の逆の移動量になっていない場合、そのままAddSpeedする
//逆向きになったら、falseを返すため、移動量を0.0にする
bool	CameraGun::CheckAddSpeed()
{
	if (object.GetDirection() == Status::Direction::Left)
	{
		if (object.GetMoveVec().x() >= 0.0f)
		{
			object.GetMoveVec().x() = 0.0f;
			return false;
		}
	}
	if (object.GetDirection() == Status::Direction::Right)
	{
		if (object.GetMoveVec().x() <= 0.0f)
		{
			object.GetMoveVec().x() = 0.0f;
			return false;
		}
	}
	return true;
}