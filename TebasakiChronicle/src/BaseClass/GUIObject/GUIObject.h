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
	GUIObject(	const std::string& imageName_,
				const K_Math::Vector3& pos_,
				const K_Math::Box2D& srcBox_);

	//!@brief デストラクタ
	~GUIObject();
	//!@brief 更新処理
	void	UpDate();
	//!@brief 描画処理
	void	Render();

	//!@brief 位置の移動処理
	//!@param[in] pos_ 移動させる位置
	void	SetPos(const K_Math::Vector3& pos_);

private:
	K_Graphics::Texture*	texture;
	GameObject		object;		//オブジェクト
	std::string		imageName;	//画像名
	K_Math::Box2D	srcBox;		//画像元のサイズ
};