#pragma once
#include "../src/BaseClass/GUIObject/GUIObject.h"


//---------------------------------------------------------------------
//概要: GUIのオブジェクト(単体のもの)
//製作者: 日比野
//---------------------------------------------------------------------
class ScreenGui
{
public:
	//!@brief	コンストラクタ
	ScreenGui();
	//!@brief	ですトラクタ
	~ScreenGui();

	//!@brief	更新
	void	UpDate();
	//!@brief	描画
	void	Render();


private:
	GUIObject*		gearLeft[5];	//歯車左側
	GUIObject*		gearRight[6];	//歯車右側
	GUIObject*		gearLife[4];	//Lifeの歯車
	GUIObject*		skillArea;		//スキルのUI
	GUIObject*		lifeneedle;		//体力の針
	GUIObject*		lifeBaseArea;	//体力の基盤

private:
	float			angle;
};