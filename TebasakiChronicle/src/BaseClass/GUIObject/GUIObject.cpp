#include "GUIObject.h"
#include "../../CSTList.h"
//#include "CameraList.h"

//-------------------------------------------------
//!@brief	コンストラクタ
//-------------------------------------------------
GUIObject::GUIObject(const std::string& imageName_,
	const K_Math::Vector3& pos_,
	const K_Math::Box2D& srcBox_,
	const int animSheet,
	const float animSpeed)
	: imageName(imageName_)
	, srcBox(srcBox_)
{
	rotateSpeed = 1.0f;
	angle = 0.0f;
	maxAngle = 360.0f;
	moveAmount = 0.0f;
	outCircleAngle = 0.0f;
	offsetSrcPos = K_Math::Vector2(0,0);

	object.SetPos(pos_);
	object.SetAngle(K_Math::Vector3(0, 0, angle));
	object.SetScale(K_Math::Vector3(1, 1, 1));
	object.SetMoveVec(object.GetPos());

	texture = CST::GetTexture(imageName);
	object.SetImage(texture, true);
	object.GetImage().CreateCharaChip(srcBox, animSheet, animSpeed, true);
}

GUIObject::GUIObject(
	const std::string& imageName,
	const std::string& filePath,
	const K_Math::Vector3& pos_,
	const K_Math::Box2D& srcBox_,
	const int animSheet,
	const float animSpeed 
)
	: imageName(imageName)
	, srcBox(srcBox_)
{
	rotateSpeed = 1.0f;
	angle = 0.0f;
	maxAngle = 360.0f;
	moveAmount = 0.0f;
	outCircleAngle = 0.0f;
	offsetSrcPos = K_Math::Vector2(0, 0);
	object.SetPos(pos_);
	object.SetAngle(K_Math::Vector3(0, 0, angle));
	object.SetScale(K_Math::Vector3(1, 1, 1));
	object.SetMoveVec(object.GetPos());

	CST::LoadAndGetTexture(imageName, filePath);
	texture = CST::GetTexture(imageName);
	object.SetImage(texture, true);
	object.GetImage().CreateCharaChip(srcBox, animSheet, animSpeed, true);
}
//-----------------------------------------------------------------------
//!@brief	デストラクタ
//-----------------------------------------------------------------------
GUIObject::~GUIObject()
{

}

//------------------------------------------------------------------------
//!@brief	更新処理
//------------------------------------------------------------------------
void	GUIObject::UpDate()
{
	object.GetImage().Animation();
}

//------------------------------------------------------------------------
//!@brief	2D空間に描画する
//------------------------------------------------------------------------
void	GUIObject::Render()
{
	object.GetImage().ImageDraw2D(object.GetPos(), object.GetAngle(), object.GetScale(), 0);
}

//------------------------------------------------------------------------
//!@brief	3D空間に描画する
//------------------------------------------------------------------------
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

//!@brief	回転角度の設定
//!@param[in]	angle	角度軸(x,y,z)
void	GUIObject::SetAngle(const K_Math::Vector3& angle)
{
	object.SetAngle(angle);
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

//!@brief	回転角度の設定
//!@param[in]	rotateAngle	回転角度
void		GUIObject::SetRotateAngle(const float rotateAngle)
{
	angle = rotateAngle;
}
//!@brief	画像ソースのオフセット量
//!@param[in]	offsetSrcPos	オフセット量(x,y)
void		GUIObject::SetOffsetSrcPos(const K_Math::Vector2& offsetSrcPos)
{
	this->offsetSrcPos = offsetSrcPos;
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
	moveCnt += 1;
	object.GetMove().SetAddVec(1);
}

//!@brief	移動量の設定
void		GUIObject::SetMoveAmount(const float moveAmount)
{
	this->moveAmount = moveAmount;
}

//!@brief	外周の回転をさせる
//!@param[in]	rotSpeed	回転速度(ラジアン)
void		GUIObject::OutCircleRotation(const float rotSpeed)
{
	this->outCircleAngle += rotSpeed;
}

//!@brief	外周回転でのGUI位置の設定
//!@param[in]	baseRotPos	回転の基準位置
//!@param[in]	distance	基準位置からの距離
void		GUIObject::SetOutCirclePos(const K_Math::Vector3& baseRotPos,const float distance)
{
	SetPos(K_Math::Vector3(baseRotPos.x + cosf(outCircleAngle) * distance, baseRotPos.y + sinf(outCircleAngle) * distance, 0));
}

//!@brief	外周での角度の設定
//!@param[in]	angle	外周での角度(ラジアン)
void		GUIObject::SetOutCircleAngle(const float angle)
{
	outCircleAngle = angle;
}

//!@brief	数字画像描画専用
//!@param[in]	numStr	数字文字列
void		GUIObject::RenderNumberImage(const char* numStr)
{
	K_Math::Vector2 distance = object.GetPos();
	for (int i = 0; i < (int)strlen(numStr); ++i)
	{
		int code = ((unsigned char)numStr[i]);
		int fx = (code - '0') * srcBox.w;
		int fy = 0 * srcBox.h;
		GetGameObject().GetImage().GetNowAnimationCharaChip()->chip = K_Math::Box2D(fx, fy, srcBox.w, srcBox.h);
		GetGameObject().GetImage().ImageDraw2D(K_Math::Vector3(distance.x, distance.y, 0), object.GetAngle(), object.GetScale(), 0);
		distance.x += offsetSrcPos.x;
		distance.y += offsetSrcPos.y;
	}
}