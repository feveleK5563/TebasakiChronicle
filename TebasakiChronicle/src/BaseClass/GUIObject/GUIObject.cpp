#include "GUIObject.h"
#include "CameraList.h"

//-------------------------------------------------
//コンストラクタ
//-------------------------------------------------
GUIObject::GUIObject(const std::string& imageName_,
	const K_Math::Vector3& pos_,
	const K_Math::Box2D& srcBox_)
	: imageName(imageName_)
	, srcBox(srcBox_)
{
	rotateSpeed = 1.0f;
	angle = 0.0f;
	maxAngle = 360.0f;

	object.SetPos(pos_);
	object.SetAngle(K_Math::Vector3(0, 0, angle));
	object.SetScale(K_Math::Vector3(1, 1, 1));
	object.SetMoveVec(object.GetPos());

	texture = new K_Graphics::Texture();
	texture->Initialize();
	texture->LoadImage("./data/image/" + imageName + ".png");
	object.SetImage(texture, true);
	object.GetImage().CreateCharaChip(srcBox, 1, 1, false);
}

//デストラクタ
GUIObject::~GUIObject()
{
	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
}
//更新処理
void	GUIObject::UpDate()
{
	object.GetImage().Animation();
}

//!@brief	2D空間に描画する
void	GUIObject::Render()
{
	object.GetImage().ImageDraw2D(object.GetPos(), object.GetAngle(), object.GetScale(), 0);
}


//!@brief	3D空間に描画する
void	GUIObject::Render3D()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
}

//!@brief 位置の移動処理
//!@param[in] pos_ 移動させる位置
void	GUIObject::SetPos(const K_Math::Vector3& pos_)
{
	object.SetPos(pos_);
}

//!@brief	位置の移動
//!@param[in] moveVec 移動量
void	GUIObject::AddVec(const K_Math::Vector3& moveVec)
{
	object.SetPos(object.GetPos() + moveVec);
}

//!@brief	大きさの設定
//!@param[in]	scale 大きさ
void	GUIObject::SetScale(const K_Math::Vector3& scale)
{
	object.SetScale(scale);
}


//!@brief	GameObjectの取得
//!@return	ゲームオブジェクト
GameObject&	GUIObject::GetGameObject()
{
	return object;
}

//!@brief	回転速度の設定
//!@param[in]	ratateSpeed_ 回転速度
void		GUIObject::SetRotateSpeed(const float rotateSpeed_)
{
	rotateSpeed = rotateSpeed_;
}

//!@brief	回転させる角度の設定
//!@param[in]	angle	回転角度(度数法)
void		GUIObject::SetRotateAngle(const float angle)
{
	maxAngle = angle;
}

//!@brief	回転
void		GUIObject::Rotation()
{
	object.SetAngle(K_Math::Vector3(0, 0, angle));
	angle += rotateSpeed;
	if (rotateSpeed < 0.0f)
	{
		if (angle >= maxAngle)
		{
			angle = 0;
		}
	}
	else
	{
		if (angle <= -maxAngle)
		{
			angle = 0;
		}
	}
}

//!@brief	移動(1フレーム加算)
void		GUIObject::AddVec()
{
	moveCnt++;
	object.GetMove().SetAddVec(1);
}

//!@brief	移動量の設定
void		GUIObject::SetMoveAmount(const float moveAmount)
{
	this->moveAmount = moveAmount;
}

//!@brief	移動が終了したか
bool		GUIObject::FinishMove()
{
	if (moveCnt <= moveAmount)
	{
		return false;
	}
	moveCnt = 0;
	return true;
}

//!@brief	回転が終了したか
bool		GUIObject::FinishRotation()
{
	if (rotateSpeed < 0.0f)
	{
		if (angle >= maxAngle)
		{
			return true;
		}
	}
	else
	{
		if (angle <= -maxAngle)
		{
			return true;
		}
	}
	return false;
}