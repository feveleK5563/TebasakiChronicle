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

	//仮のライフ処理
	void	RaitoRaito();

private:
	GUIObject*	lifeNeedle;	//ライフの針
	float	angle;			//角度
	float	maxAngle;		//最大角度
	float	minAngle;		//最小角度
	float	raito;			//割合
	float	decreaseAmount;	//減らす量
	int		life;
	int		maxLife;
	float	timeCnt;
	bool	upDataFlag;	
};