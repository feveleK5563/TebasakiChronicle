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
	explicit GageGui(GameObject& object);
	//!@brief	デストラクタ
	~GageGui();
	//!@brief	更新
	void		UpDate(GameObject& object);
	//!@brief	描画
	void		Render();
	//!@brief	イベントを開始する
	//!@brief	呼ぶとイベントを開始する
	void		EventStart();

private:
	//!@brief	状態変更部分
	void	Think();
	//!@brief	処理部分
	void	Process();
	//!@brief	モーションの更新
	//!@param[in]	eventMotion	現在のイベントモーション
	void	UpDateEventMotion(const EventMotion& eventMotion);
	//!@brief	ゲージを変動させます
	void	Fluctuation(const K_Math::Vector3& targetPos);
	//!@brief	リセット
	void	Reset(GameObject& object);
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
	int				moveCnt;		//移動する時間
	int				rotateCnt;		//回転する時間
	int				maxMoveCnt;		//最大移動時間
	int				maxRotateCnt;	//最大回転時間
	K_Math::Vector3	maxShowLife;	//最大hpゲージ位置
	K_Math::Vector3	minShowLife;	//最小hpゲージ位置
	K_Math::Vector3 showLife;		//hpゲージ位置
	float			changeAmount;	//変化量
	EventMotion		eventMotion;	//イベントモーション
	bool			eventStartFlag;	//イベントスタートフラグ
};