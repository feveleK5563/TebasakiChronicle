#pragma once
#include "../src/BaseClass/GUIObject/GUIObject.h"


//---------------------------------------------------------------------
//概要: データを表示させるGUI(単体のもの)
//製作者: 日比野
//---------------------------------------------------------------------
class DataGui
{
public:
	//!@brief	コンストラクタ
	DataGui(GameObject& gameObj);
	//!@brief	デストラクタ
	~DataGui();

	//!@brief	更新
	void	UpDate();
	//!@brief	描画
	void	Render();

	//!@brief	割合の計算
	//!@param[in]	gameObj	ゲームオブジェクト
	void	Raito(GameObject& gameObj);

private:
	//!@brief	針の変動処理
	void	Fluctuation(const K_Math::Vector3& targetPos);

private:
	GUIObject*	lifeNeedle;		//ライフの針
	float		maxAngle;		//最大角度
	float		minAngle;		//最小角度
	float		raito;			//割合
	float		changeAmount;	//変化量
	float		offsetAngle;	//オフセット値
	K_Math::Vector3	showLife;

	int		life;
	int		maxLife;
	float	timeCnt;
};