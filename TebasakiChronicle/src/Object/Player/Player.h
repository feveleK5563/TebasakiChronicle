#pragma once
#include "../src/Object//Player/CameraGun/CameraGun.h"
#include "../src/Object/Player/CharaController/CharaController.h"
#include "../src/Object/Player/Skill/SkillManager.h"


//--------------------------------------------------------------------
//プレイヤー
//概要:プレイヤー専用
//製作者:日比野
//--------------------------------------------------------------------
class Player
{
public:
	//モーション
	enum Motion
	{
		Non = -1,	//なし
		Idle = 0,	//待機
		Walk,		//歩く
		Run,		//走る
		Jump,		//上昇中
		Fall,		//落下中
		TakeOff,	//飛ぶ前
		Landing,	//着地
		SkillUse,		//停止中にスキル使用
		SkillMoveUse,	//移動中にスキル使用
		SkillAirUse,	//空中でスキル使用
		CameraGunUse,		//カメラガン停止中に構え
		CameraGunMoveUse,	//カメラガン移動中に構え
		CameraGunAirUse,	//カメラガン空中で構え
		DamageRecive,		//ダメージ受ける
		Death,				//死亡
	};

	
	//コリジョンの種類
	enum CollisionKind
	{
		Base = 0,	//体
		Foot,		//足元
		Head,		//頭上
	};

	//アニメーションモーション
	enum class AnimState
	{
		Non = -1,
		Idle = 0,		//待機
		Walk,			//出だし
		RightRun,		//右足
		LeftRun,		//左足
		Jump,			//ジャンプ
		Fall,			//落下
		Landing,		//着地
		GunRightRun,	//右足カメラガン
		GunLeftRun,		//左足カメラガン
		GunJump,		//ジャンプカメラガン
		GunFall,		//落下カメラガン
		GunIdle,		//待機中のカメラガン
		Damage,			//ダメージ
	};

public:
	Player();
	~Player();

	void	Initliaze();	//初期化
	void	UpDate();		//更新
	void	Render();		//描画

	//ダメージを与える
	int		GiveDamage();
	//ダメージの受ける処理
	void	ReciveDamage();

	//!@brief	オブジェクトの取得
	GameObject&	GetGameObject();

private:
	void	ChangeDir();		//入力に応じて向きを変える
	void	ShotCameraGun();	//カメラガンを飛ばす
	void	ReverseCameraGun();	//カメラガンを戻す
	void	JumpMove();			//ジャンプ

	void	Think();	//思考処理(モーション決定)
	void	Move();		//モーションに対応した処理
	bool	UpDateMotion(const Motion& nowMotion);	//モーションの更新

private:
	
	//!@brief スキルの登録処理
	void	RegistSkill();
	//!@brief スキルの使用処理
	void	UseSkill();

	//!@brief スキルの状態変異
	void	SkillState(Motion& nowMotion,const Motion& nextMotion,const int& btnNum);
	//!@brief スキルの状態へ
	void	ChangeSkillMotion(Motion& nowMotion,const Motion& nextMotion);

	//!@brief ダメージモーションへチェンジ
	void	ChangeDamageMotion(Motion& motion);

	//!@brief ノックバック処理
	//!@param[in] 相手の座標
	void	KnockBack(const K_Math::Vector3& pos_);

	//!@brief	点滅処理
	bool	Flashing();

	//!@brief	アニメーション状態の変更
	//!@param[in]	animState	アニメーション状態
	void	ChangeAnimState(const AnimState& animState);
	
	//!@brief	アニメーション状態の更新
	//!@param[in]	animState	アニメーション状態
	void	UpDateAnimState(const AnimState& animState);

	//!@brief	アニメーション切り替え
	//!@brief	2つのアニメーションを切り替える処理
	//!@param[in]	animState1	アニメーション状態1
	//!@param[in]	animState2	アニメーション状態2
	//!@param[in]	frameCnt	切り替えるフレーム数
	void	SwitchAnimState(const AnimState& animState1,const AnimState& animState2,const float frameCnt);

private:
	//--------------------------------
	//エフェクト

private:
	GameObject		object;				//ゲームオブジェクト
	Status*			enemyData;			//敵のステータス
private:
	Motion			motion;				//モーション
	int				preMotionCnt;		//前のモーションカウント
	int				motionCnt;			//モーションのカウント
	CharaController	controller;			//コントローラー
	CameraGun		cameraGun;			//カメラガン
	SkillManager	skillManager;		//スキル
	int				maxFrame;			//最大のフレーム数
	float			minJumpForce;		//最低限のジャンプ
	int				invicibleCnt;		//無敵時間カウント
	int				maxInvicibleTime;	//最大無敵時間
	AnimState		preAnimState;		//1つ前のアニメーション状態
	AnimState		animState;			//アニメーションの状態
public:
	K_Physics::CollisionShape*	shape;		//ベースコリジョンの形状
	K_Physics::CollisionShape*	shape2;		//足元と頭上用コリジョンの形状
	CollisionManager			cManager;	//コリジョンの管理者

	K_Graphics::Texture*		texture;

};

