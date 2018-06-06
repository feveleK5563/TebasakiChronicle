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

	//!@brief	描画
	void		Render();
private:
	GUIObject	guiObject;	//GUIオブジェクト
	float		result;
	float		baseAngle;
};