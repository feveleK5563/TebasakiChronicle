#pragma once
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/GUIObject/GUIObject.h"

//---------------------------------------------------------------------
//概要: ゲージを扱うGUIオブジェクト(単体のもの)
//製作者: 日比野
//---------------------------------------------------------------------
class GageGui 
{
public:
	//!@brief	コンストラクタ
	GageGui();
	//!@brief	デストラクタ
	~GageGui();

	//!@brief	割合を算出する
	void		Raito(float maxValue,float nowValue,float raito);

	//!@brief	位置に割合を適用する
	void		ProcessPos();
	//!@brief	角度に割合を適用する
	void		ProcessRotation();
	//!@brief	大きさ割合を適用する
	void		ProcessScale();

	//!@brief	更新
	void		UpDate();
	//!@brief	描画
	void		Render();

private:
	//!@brief	位置を指定した数動かす
	void	AddMove(float moveAmount);
	//!@brief	回転量を与える
	void	AddRotation(float angleAmount);
	//!@brief	出現
	void	Appear();

	//!@brief	位置の移動
	void	Move();
	//!@brief	回転
	void	Rotate();

private:
	GUIObject		frame;			//枠
	GUIObject		backGround;		//下に配置するゲージ
	GUIObject		fillAreaBox;	//上に配置するゲージ

private:
	float			nowGagePos;		//ゲージの現在位置
	int				moveMotion;
};