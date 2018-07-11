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
	effectCreateFlag = true;
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

	object.GetMove().SetAddVec(5.0f);

	//動きの初期化
	//動きはデフォルトで生成させる
	object.SetImage(CST::LoadAndGetTexture("target", "data/image/target.png"), true);
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 32, 32), 1, 1, false);

	//ボックスの形の生成
	shape = CC::CreateBoxShape(10, 10, 1);

	//生成した[形]でコリジョンや剛体を作成
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), false);
	cManager.CreateSubCollisionData(shape, CollisionMask::EnemyCamCollision, CollisionMask::CameraGunCollision, object.GetPos());

	//コリジョンに情報を持たせる
	cManager.SetSubCollisionUserData(0, &object.GetState());
	targetNum = -1;
	targetData = nullptr;
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
		if (CheckUserData())
		{
			K_Math::Vector3	tarPos = *targetData->pos;
			Chase(tarPos);
			//エフェクト******
			//if (effectCreateFlag)
			//{
			//	//仮のエフェクト
			//	Effect::CreateEffect(EffectName::Effect1, object.GetPos());
			//	effectCreateFlag = false;
			//}
		}
		else
		{
			//衝突していない場合、向いている方向にすすみ続ける
			object.GetPos() += object.GetMoveVec();
			float addSpeed = -GetDir() * 0.05f;
			if (CheckAddSpeed())
			{
				object.GetMoveVec().x += addSpeed;
			}
			RecieveData();

			//エフェクトを作成できるようにする
			//effectCreateFlag = true;
		}
	}
	
	//アニメーション処理
	object.GetImage().Animation();

	//カメラガンの移動
	cManager.MoveBaseCollision(object.GetMoveVec(), object.GetDirection(), true);
	//コリジョンの位置の同期
	object.GetPos() = cManager.GetBaseCollisionObjectPosition();
	object.GetPos().z = -1.f;
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
	cManager.SetBaseCollisionObjectPosition(pos);
	object.SetMoveVec(K_Math::Vector3(0, 0, 0));
}


//追尾処理
void	CameraGun::Chase(const K_Math::Vector3& targetPos)
{
	//敵とカメラガンとの距離
	K_Math::Vector3 targetVec = targetPos - object.GetPos();
	object.GetMoveVec().x = targetVec.x / object.GetMove().GetAddVec();
	object.GetMoveVec().y = targetVec.y / object.GetMove().GetAddVec();
}

//敵との衝突をした場合、スキルデータを取得する
void	CameraGun::RecieveData()
{
	//当たり判定処理
	std::vector<K_Physics::CollisionTag*> data = cManager.GetConflictionObjectsTag(0);
	if (data.size() > 0)
	{
		targetNum = data[0]->tagIndex;
		targetData = (Enemy::SkillAndCharaChip*)data[0]->userData;
	}
}


//ユーザーデータがあるかのチェック
bool	CameraGun::CheckUserData()
{
	if (targetData == nullptr)
		return false;

	std::vector<K_Physics::CollisionTag*> data = cManager.GetConflictionObjectsTag(0);
	if (data.size() > 0)
	{
		for (auto it : data)
		{
			if (targetNum == it->tagIndex)
			{
				return true;
			}
		}
	}

	SetCameraGun(false);
	return false;
}


//ベクトルの設定
//状態の設定
void	CameraGun::SetCameraGun(bool isInjection)
{
	if (isInjection)
	{
		object.SetState(Status::State::Active);
		object.SetMoveVec(K_Math::Vector3(GetDir() * object.GetMove().GetAddVec(), 0, 0));
	}
	else
	{
		object.SetMoveVec(K_Math::Vector3(0, 0, 0));
		object.SetState(Status::State::Non);
		object.GetMove().SetAddVec(5.0f);	//元に戻す
		DataReset();
	}
}

//カメラガンの移動速度の設定
void	CameraGun::SetMoveSpeed(float moveSpeed)
{
	object.GetMove().SetAddVec(moveSpeed);
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
		if (object.GetMoveVec().x >= 0.0f)
		{
			object.GetMoveVec().x = 0.0f;
			return false;
		}
	}
	if (object.GetDirection() == Status::Direction::Right)
	{
		if (object.GetMoveVec().x <= 0.0f)
		{
			object.GetMoveVec().x = 0.0f;
			return false;
		}
	}
	return true;
}

void	CameraGun::DataReset()
{
	targetNum = -1;
	targetData = nullptr;
}


//!@brief カメラガンが受け取ったスキルデータを渡す
//!@return skillAndCharaChip スキルのデータ
Enemy::SkillAndCharaChip& CameraGun::GetSkillAndCharaChip()
{
	return *targetData;
}