#include "Enemy.h"
#include "../../CSTList.h"
#include "../../Helper.h"

//コンストラクタ
Enemy::Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum, bool isBoss) :
	behaviorId(0),
	nowMoveOrder(0),
	nowPatternOrder(0),
	beforeMoveOrder(0),
	beforePatternOrder(0),
	isBoss(isBoss)
{
	SetEnemyType(cpyet, setPos, direction, indexNum);
}

//デストラクタ
Enemy::~Enemy()
{
	Memory::SafeDelete(skillAndChip);
}

//-----------------------------------------------------------------------------
//敵情報を設定
void Enemy::SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum)
{
	ems = cpyet->GetEnemyMoveSet();
	gameObject.GetStatus().SetStatusData(	Status::State::Non,
											setPos,
											K_Math::Vector3(0, 0, 0),
											K_Math::Vector3(1, 1, 1),
											direction,
											cpyet->GetHitDamage(),
											cpyet->GetMaxLife());
	gameObject.GetStatus().SetCollisionMask(CollisionMask::TakeDamagePlayer);

	if (cpyet->GetIsUseGravity() == false)
	{
		gameObject.GetMove().SetGravity(0.f);
	}

	initialPos = setPos;
	gameObject.GetStatus().GetMaxLife() = cpyet->GetMaxLife();
	isUseGravity = cpyet->GetIsUseGravity();

	gameObject.GetMove().SetAddVec(cpyet->GetMoveSpeed());
	gameObject.GetMove().SetJumpPow(cpyet->GetJumpPower());

	//アニメーションと表示画像の設定
	gameObject.SetImage(cpyet->GetTexture(), false);
	gameObject.GetImage().ChangeAnimationPattern(nowMoveOrder);
	gameObject.GetImage().ChangeCharaChip(ems->GetNowAnimChip(nowPatternOrder));

	//コリジョンの設定
	collisionManager.SetBaseCollisionData(cpyet->CreateAndGetBaseCollisionData(), setPos);	//ベースコリジョン
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetRecieveDamageCollisionData());	//0 被ダメージ用コリジョン
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetVisibilityCollisionData());		//1 視界用コリジョン
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetAttackAreaCollisionData());		//2 攻撃動作遷移用コリジョン
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetCheckFootCollisionData());		//3 足元判定用コリジョン
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetCheckHeadCollisionData());		//4 頭上判定用コリジョン
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetRecieveCameraCollisionData());	//5 被カメラガン用コリジョン

	for (int i = 0; i < subCollisionNum; ++i)
	{
		collisionGiveMask[i] = collisionManager.GetSubCollisionGiveMask(i);
		collisionMyselfMask[i] = collisionManager.GetSubCollisionMyselfMask(i);
	}

	//タグの設定
	skillAndChip = new SkillAndCharaChip();
	skillAndChip->pos = &gameObject.GetStatus().GetPos();
	skillAndChip->textureName = &cpyet->GetTextureName();
	skillAndChip->behaviorId = &behaviorId;
	int i = 0;
	for (; i < 5; ++i)
	{
		collisionManager.SetSubCollisionTagIndex(i, indexNum);
		collisionManager.SetSubCollisionUserData(i, &gameObject.GetStatus());
	}
	collisionManager.SetSubCollisionTagIndex(i, indexNum);
	collisionManager.SetSubCollisionUserData(i, skillAndChip);
	SetTugData();

	SetNonEnemy();
	gameObject.SetState(Status::State::Non);
}

//-----------------------------------------------------------------------------
//無効状態にする
void Enemy::SetNonEnemy()
{
	//カメラマン受け用コリジョンを除いたサブコリジョンのマスクを無効にする
	for (int i = 0; i < subCollisionNum; ++i)
	{
		collisionManager.SetSubCollisionGiveMask(i, CollisionMask::Non);
		collisionManager.SetSubCollisionMyselfMask(i, CollisionMask::Non);
	}
	tempCollisionManager.DeleteCollision();
}

//-----------------------------------------------------------------------------
//状態を全て初期状態に戻す
void Enemy::ResetAndActiveEnemy()
{
	collisionManager.SetBaseCollisionObjectPosition(initialPos);
	gameObject.SetState(Status::State::Active);
	timeCnt.ResetCntTime();
	gameObject.GetStatus().GetLife() = gameObject.GetStatus().GetMaxLife();
	behaviorId = 0;
	nowMoveOrder = 0;
	nowPatternOrder = 0;
	beforeMoveOrder = 0;
	beforePatternOrder = 0;
	//カメラマン受け用コリジョンを除いたサブコリジョンのマスクを有効にする
	for (int i = 0; i < subCollisionNum; ++i)
	{
		collisionManager.SetSubCollisionGiveMask(i, collisionGiveMask[i]);
		collisionManager.SetSubCollisionMyselfMask(i, collisionMyselfMask[i]);
	}
	//アニメーションのリセット
	gameObject.GetImage().ChangeCharaChip(ems->GetNowAnimChip(nowPatternOrder));
	gameObject.GetImage().ChangeAnimationPattern(nowMoveOrder);
}

//-----------------------------------------------------------------------------
//更新
void Enemy::Update()
{
	if (isBoss == false)
	{
		if (DecisionInScreen())
			return;
	}
	else if (gameObject.GetState() != Status::State::Active)
	{
		return;
	}

	//移動量をゼロクリア
	gameObject.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);

	//重力を加算する
	gameObject.GetMove().GravityOperation(collisionManager.GetConflictionObjectsTag(3).size() > 0);

	//接触しているコリジョンを調べてダメージを受ける
	bool isTakeDamage = RecieveCollisionOperation();

	//設定されている動作を行う
	*skillAndChip->behaviorId = ems->EMove(nowMoveOrder, nowPatternOrder, timeCnt, collisionManager, tempCollisionManager, gameObject.GetStatus(), gameObject.GetMove(), isTakeDamage);

	//アニメーションの更新
	AnimationUpdate();

	//コリジョンを動かす
	collisionManager.MoveBaseCollision(gameObject.GetMove().GetMoveVec(), gameObject.GetStatus().GetDirection(), true);
	gameObject.GetPos() = collisionManager.GetBaseCollisionObjectPosition();
	tempCollisionManager.Update();
	//タグ情報を更新
	SetTugData();

	return;
}

//-----------------------------------------------------------------------------
//死亡している否かを返す
bool Enemy::IsDead()
{
	return gameObject.IsDead();
}

//-----------------------------------------------------------------------------
//画面内判定
bool Enemy::DecisionInScreen()
{
	//画面外に出ていたら無効
	if (fabsf(CST::GetPerspectiveCamera()->GetPosition().x - gameObject.GetPos().x) > fabsf(Define::ScreenWidth / 2))
	{
		if (gameObject.GetState() != Status::State::Non)
		{
			gameObject.SetPos(initialPos);
			SetNonEnemy();
			gameObject.SetState(Status::State::Non);
		}
		return true;
	}

	//画面内に入っている、かつ死んでいない場合は有効にする
	if (gameObject.GetState() == Status::State::Non)
	{
		ResetAndActiveEnemy();
	}
	else if (gameObject.GetState() == Status::State::Death)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//コリジョンとの接触処理
//ダメージを受けたらtrueを返す
bool Enemy::RecieveCollisionOperation()
{
	if (gameObject.GetState() == Status::State::Invalid)
		return false;

	std::vector<K_Physics::CollisionTag*> tag;

	int damage = 0;	//被ダメージ

	//ダメージを受ける
	tag = collisionManager.GetConflictionObjectsTag(Enemy::EnemyCollisionName::RecieveDamage);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			damage += ((Status*)it->userData)->GetAttackPoint();
		}
	}

	//カメラガンを受ける
	tag = collisionManager.GetConflictionObjectsTag(Enemy::EnemyCollisionName::RecieveCameraGun);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			//カメラガンから受ける影響をここに記述

		}
	}

	//ダメージを体力に反映
	gameObject.GetStatus().GetLife() -= damage;

	//体力が0以下になったら死亡
	if (gameObject.GetStatus().GetLife() <= 0)
	{
		SetNonEnemy();	//敵を無効にする
		gameObject.SetState(Status::State::Death);	//ステータスをDeathに変更

		//(仮)爆発エフェクトの発生
		Effect::CreateEffect(EffectName::Effect1, gameObject.GetPos());
	}

	return damage > 0;
}

//-----------------------------------------------------------------------------
//タグに情報を格納
void Enemy::SetTugData()
{
	skillAndChip->nowCharaChip = gameObject.GetImage().GetNowAnimationCharaChip();
}

//-----------------------------------------------------------------------------
//アニメーションの更新
void Enemy::AnimationUpdate()
{
	gameObject.GetImage().Animation();

	//現在の動作と前の動作が異なる場合アニメーションパターンを変更する
	if (beforeMoveOrder != nowMoveOrder)
	{
		gameObject.GetImage().ChangeAnimationPattern(nowMoveOrder);
	}
	beforeMoveOrder = nowMoveOrder;

	//現在の動作パターンと前のパターンが異なる場合キャラチップを変更する
	if (beforePatternOrder != nowPatternOrder)
	{
		gameObject.GetImage().ChangeCharaChip(ems->GetNowAnimChip(nowPatternOrder));
	}
	beforePatternOrder = nowPatternOrder;
}

//-----------------------------------------------------------------------------
//描画
void Enemy::Render()
{
	if (gameObject.GetState() != Status::State::Active ||
		(gameObject.GetState() == Status::State::Invalid && (timeCnt.GetNowCntTime() % 2) == 0))
		return;

	gameObject.GetImage().ImageDraw3D(	gameObject.GetStatus().GetPos(),
										gameObject.GetStatus().GetAngle(),
										gameObject.GetStatus().GetScale(),
										gameObject.GetStatus().GetDirection());
	tempCollisionManager.Render();
}