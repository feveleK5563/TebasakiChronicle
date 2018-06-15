#pragma once
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/ImageManager/ImageManager.h"


//---------------------------------------------------------------------
//概要: GUIのオブジェクト(単体のもの)
//製作者: 日比野
//---------------------------------------------------------------------
class GUIObject
{
public:
	//!@brief コンストラクタ
	//!@param[in] imageName_ 画像名
	//!@param[in] pos_	位置
	//!@param[in] srcBox_ 画像元のサイズ
	GUIObject(const std::string& imageName_,
		const K_Math::Vector3& pos_,
		const K_Math::Box2D& srcBox_);

	//!@brief デストラクタ
	~GUIObject();
	//!@brief 更新処理
	void	UpDate();
	//!@brief 2D空間に描画する
	void	Render();
	//!@brief	3D空間に描画する
	void	Render3D();

	//!@brief 位置の設定
	//!@param[in] pos_ 移動させる位置
	void	SetPos(const K_Math::Vector3& pos_);

	//!@brief	位置の移動
	//!@param[in] moveVec 移動量
	void	AddVec(const K_Math::Vector3& moveVec);

	//!@brief	大きさの設定
	//!@param[in]	scale 大きさ
	void	SetScale(const K_Math::Vector3& scale);

	//!@brief	GameObjectの取得
	//!@return	ゲームオブジェクト
	GameObject&	GetGameObject();

	//!@brief	回転速度の設定
	//!@param[in]	ratateSpeed_ 回転速度
	void		SetRotateSpeed(const float rotateSpeed_);
	//!@brief	回転させる角度の設定
	//!@param[in]	angle	回転角度(度数法)
	void		SetRotateAngle(const float angle);
	//!@brief	回転
	void		Rotation();
	//!@brief	移動(1フレーム加算)
	void		AddVec();
	//!@brief	移動量の設定
	void		SetMoveAmount(const float moveAmount);

	//!@brief	移動が終了したか
	bool		FinishMove();
	//!@brief	回転が終了したか
	bool		FinishRotation();
private:
	K_Graphics::Texture*	texture;
	GameObject				object;			//オブジェクト
	std::string				imageName;		//画像名
	K_Math::Box2D			srcBox;			//画像元のサイズ
	float					rotateSpeed;	//回転速度
	float					angle;			//向き
	float					maxAngle;		//最大角度
	float					moveCnt;		//移動カウント
	float					moveAmount;		//移動させる量
};