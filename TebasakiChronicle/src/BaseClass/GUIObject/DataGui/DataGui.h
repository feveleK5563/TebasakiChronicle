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

private:
	K_Graphics::Texture*	texture;
	GameObject		object;		//オブジェクト
	std::string		imageName;	//画像名
	K_Math::Box2D	srcBox;		//画像元のサイズ

};