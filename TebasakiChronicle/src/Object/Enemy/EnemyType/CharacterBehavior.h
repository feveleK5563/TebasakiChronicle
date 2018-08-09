#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../Effect/Effect.h"
#include "../../GameObject.h"
#include "../../TemporaryCollision/TemporaryCollisionManager.h"
#include "../../../TimeCount.h"
#include "../../../Helper.h"

//-----------------------------------------------------------------------------
//動作の抽象クラス
class CharacterBehaviorAbstract
{
public:
	virtual ~CharacterBehaviorAbstract();
	virtual void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) = 0;
	virtual void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) = 0;
	virtual void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) = 0;
};

//-----------------------------------------------------------------------------
//動作の設定と管理を行うクラス
class CharacterBehavior
{
private:
	CharacterBehaviorAbstract*	behavior;

public:
	CharacterBehavior(int moveNum);
	~CharacterBehavior();

	//動作を設定する
	void SetBehavior(int moveNum);

	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject, TimeCount& timeCnt);
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject);
};


/* 動作追加のためのテンプレ

//-----------------------------------------------
//
class Behavior_ : public CharacterBehaviorAbstract
{
public:
void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

*/

//-----------------------------------------------
//何もしない
class Behavior_NoMotion : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//向きを変更する
class Behavior_ChangeDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//向いている方向に移動する
class Behavior_MovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//無条件に一回だけジャンプする
class Behavior_OnceJump : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//前方に攻撃する
class Behavior_FrontAttack : public CharacterBehaviorAbstract
{
private:
	void CreateAttackCollision();

public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//重力の有無を切り替える
class Behavior_SwitchingGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//重力を無効にして浮く
class Behavior_DisableGravityAndFloat : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//一時的に重力を無効にし、一定速度で落下する
class Behavior_Fall : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//重力を一時的に半分にする
class Behavior_ToHarfGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//空中で上下に揺れる
class Behavior_AirIdle : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//空中で上下に揺れながら向いている方向に移動する
class Behavior_AirMovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//Y座標の真ん中から前方に弾を発射する
class Behavior_ShotBulletFromMiddle : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//重力アリの爆弾を投げる
class Behavior_ThrowBomb : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager,  GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//視界内のプレイヤーのX軸に合わせる
class Behavior_MovePlayerPosX : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//視界内のプレイヤーのY軸に合わせる
class Behavior_MovePlayerPosY : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//初期配置時の座標に移動する
class Behavior_MoveInitPos : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//一時的に重力を無効にし急速落下、動作終了時にエフェクトを発生させる
class Behavior_HighSpeedFall : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//コリジョンマスクを全て無効にする
class Behavior_NonActiveCollisionMask : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//コリジョンマスクを全て有効にする
class Behavior_ActiveCollisionMask : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//ビームを撃つ
class Behavior_Beam : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//向いている方向に高速で移動する
class Behavior_HighSpeedMove : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};