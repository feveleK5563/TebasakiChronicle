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

//-------------------------------------------------
//デストラクタ
//-------------------------------------------------
CameraGun::~CameraGun()
{

}


//更新処理
void	CameraGun::UpDate()
{
	//カメラが有効かどうか
	if (!active) { return; }

	//敵と衝突した場合
	if (HitEnemy())
	{
		K_Math::Vector3 tarPos;	//衝突した敵の位置
		Chase(tarPos);			//追尾
	}
	else //衝突しない場合
	{
		K_Math::Vector3 moveVec;	//移動量
		K_Math::Vector3	dir;		//向き
		K_Math::Vector3 myPos;		//自分の位置

		//---Vector3などは、*演算子で計算ができない---
		//myPos += moveVec * dir;		//その向きに移動量分、位置を更新
	}
}



//追尾処理
void	CameraGun::Chase(const K_Math::Vector3& targetPos)
{
	//自身の位置
	K_Math::Vector3 pos = { 0,0,0 };

	//敵とカメラガンとの距離
	K_Math::Vector3 targetVec = targetPos - pos;

	//チェック判定
	if (targetVec.x() == 0 && targetVec.y() == 0)
	{
		//敵との座標はすでにあっている
		return;
	}

	//追尾
	float angle = atan2f(targetVec.y(), targetVec.x());	//角度
	float speed = 3.0f;		//スピード
	pos.x() += cos(K_Math::DegToRad(angle)) * speed;
	pos.y() += sin(K_Math::DegToRad(angle)) * speed;
}




//-------------
//仮処理
//-------------
void	CameraGun::Initailize()
{
	//ステータスの設定
	object.GetStatus().SetStatusData(
		Status::State::Non,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Right,
		1,
		0);
	
	//動きの初期化
	//動きはデフォルトで生成させる

	//画像の設定
	//使い方は今は不明
	//object.GetImage()->

	//Easingは初期化の必要はない
}

void	CameraGun::Render()
{

}

bool	CameraGun::HitEnemy()
{
	return true;
}