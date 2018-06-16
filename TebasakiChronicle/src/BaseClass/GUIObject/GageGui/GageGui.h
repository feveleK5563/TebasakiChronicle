#pragma once
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/GUIObject/GUIObject.h"

//---------------------------------------------------------------------
//概要: ゲージを扱うGUIオブジェクト(単体のもの)
//製作者: 日比野
//---------------------------------------------------------------------
class GageGui 
{
private:
	//!@brief	イベントモーション
	enum EventMotion
	{
		Ev_Non = 0,		//なし
		Ev_Begin,		//開始
		Ev_Move,		//移動
		Ev_Rotate,		//回転
		Ev_End,			//終了
	};
public:
	//!@brief	コンストラクタ
	GageGui();
	//!@brief	デストラクタ
	~GageGui();

	//!@brief	割合を算出する
	void		Raito(float maxValue,float nowValue,float raito);

	//!@brief	位置に割合を適用する
	void		ProcessPos();

	//!@brief	更新
	void		UpDate();
	//!@brief	描画
	void		Render();

private:
	//!@brief	状態変更部分
	void	Think();
	//!@brief	処理部分
	void	Process();
	//!@brief	モーションの更新
	//!@param[in]	eventMotion	現在のイベントモーション
	void	UpDateEventMotion(const EventMotion& eventMotion);

private:
	//コピーを禁止します
	explicit GageGui(const GageGui& gageGui);
	GageGui& operator=(const GageGui& gageGui);

private:
	GUIObject		frame;			//枠
	GUIObject		fillAreaBox;	//上に配置するゲージ

private:	//仮
	int		minLife;
	int		maxLife;
	int		life;
private:
	float			nowGagePos;		//ゲージの現在位置
	int				moveCnt;		//移動する時間
	int				rotateCnt;		//回転する時間
	int				beginCnt;		//初めのカウント
	int				maxMoveCnt;		//最大移動時間
	int				maxRotateCnt;	//最大回転時間
	K_Math::Vector3	maxShowLife;	//最大hpゲージ位置
	K_Math::Vector3	minShowLife;	//最小hpゲージ位置
	float			showLife;		//hpゲージ位置
	int				timeCnt;
	EventMotion		eventMotion;	//イベントモーション
};