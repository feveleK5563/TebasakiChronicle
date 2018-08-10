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
	isBoss(isBoss),
	relativePos(0.f, 0.f, 0.f)
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

	gameObject.GetStatus().GetInitialPos() = setPos;
	gameObject.GetStatus().GetMaxLife() = cpyet->GetMaxLife();
	gameObject.GetStatus().GetMinLife() = 0;
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
	SetTagData();

	SetNonEnemy();
	gameObject.SetState(Status::State::Non);

	timeCnt.SetEndTime(-1);
	invalidTime.SetEndTime(20);
	invalidTime.Count(false);
}

//-----------------------------------------------------------------------------
//無効状態にする
void Enemy::SetNonEnemy()
{
	//カメラマン受け用コリジョンを除いたサブコリジョンのマスクを無効にする
	collisionManager.SetMaskActive(false);
	tempCollisionManager.DeleteCollision();
}

//-----------------------------------------------------------------------------
//状態を全て初期状態に戻す
void Enemy::ResetAndActiveEnemy()
{
	collisionManager.SetBaseCollisionObjectPosition(gameObject.GetStatus().GetInitialPos());
	gameObject.SetState(Status::State::Active);
	timeCnt.ResetCntTime();
	gameObject.GetStatus().GetLife() = gameObject.GetStatus().GetMaxLife();
	behaviorId = 0;
	nowMoveOrder = 0;
	nowPatternOrder = 0;
	beforeMoveOrder = 0;
	beforePatternOrder = 0;
	//カメラマン受け用コリジョンを除いたサブコリジョンのマスクを有効にする
	collisionManager.SetMaskActive(true);
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
	else if (	gameObject.GetState() == Status::State::Death ||
				gameObject.GetState() == Status::State::Non)
	{
		return;
	}

	//移動量を初期化
	gameObject.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);

	//重力を加算する
	gameObject.GetMove().GravityOperation(collisionManager.GetConflictionObjectsTag(3).size() > 0);

	//設定されている動作を行う
	*skillAndChip->behaviorId = ems->EMove(nowMoveOrder, nowPatternOrder, timeCnt, &collisionManager, tempCollisionManager, gameObject);

	//アニメーションの更新
	AnimationUpdate();

	//コリジョンを動かす
	collisionManager.MoveBaseCollision(gameObject.GetMove().GetMoveVec(), gameObject.GetStatus().GetDirection(), true);
	gameObject.GetPos() = collisionManager.GetBaseCollisionObjectPosition();
	tempCollisionManager.Update();
	relativePos += gameObject.GetMove().GetMoveVec();
	//タグ情報を更新
	SetTagData();

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
			gameObject.SetPos(gameObject.GetStatus().GetInitialPos());
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
	if (gameObject.GetState() != Status::State::Active)
	{
		if (gameObject.GetState() == Status::State::Invalid)
		{
			invalidTime.Run();
			if (invalidTime.IsTimeEnd())
			{
				gameObject.SetState(Status::State::Active);
			}
		}
		return false;
	}

	std::vector<K_Physics::CollisionTag*> tag;

	int damage = 0;	//被ダメージ

	//ダメージを受ける
	tag = collisionManager.GetConflictionObjectsTag(EnemyCollisionName::RecieveDamage);
	for (auto it : tag)
	{
		Status* hitThing = (Status*)it->userData;
		if (hitThing->GetState() == Status::State::Active)
		{
			damage += hitThing->GetAttackPoint();
			hitThing->GetState() = Status::State::Death;
		}
	}

	//カメラガンを受ける
	tag = collisionManager.GetConflictionObjectsTag(EnemyCollisionName::RecieveCameraGun);
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

	//ダメージを受けたら一定時間無敵状態になる
	bool isTakeDamage = damage > 0;
	if (gameObject.GetLife() > 0 && isTakeDamage)
	{
		gameObject.GetState() = Status::State::Invalid;
		invalidTime.ResetCntTime();
	}

	return isTakeDamage;
}

//-----------------------------------------------------------------------------
//タグに情報を格納
void Enemy::SetTagData()
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
	if (gameObject.GetState() == Status::State::Non ||
		gameObject.GetState() == Status::State::Death)
	{
		return;
	}

	K_Math::Vector4 color(1.f, 1.f, 1.f, 1.f);
	if (gameObject.GetState() == Status::State::Invalid)
	{
		if ((timeCnt.GetNowCntTime() % 10) < 5)	color = { 5.f, 5.f, 2.5f, 1.f };
		else									return;
	}

	gameObject.GetImage().ImageDraw3D(gameObject.GetStatus().GetPos(),
		gameObject.GetStatus().GetAngle(),
		gameObject.GetStatus().GetScale(),
		gameObject.GetStatus().GetDirection(),
		color);
	tempCollisionManager.Render();
}


//--------------------------------------------------------


//座標を設定
void Enemy::SetPos(const K_Math::Vector3& setPos)
{
	gameObject.SetPos(setPos);
	collisionManager.SetBaseCollisionPos(setPos);
	collisionManager.SetSubCollisionPos(gameObject.GetDirection());
}

//相対座標を設定
void Enemy::SetRelativePos(const K_Math::Vector3& rePos)
{
	relativePos = rePos;
}

//座標を取得する
const K_Math::Vector3& Enemy::GetPos()
{
	return gameObject.GetPos();
}

//座標をオフセット
void Enemy::OffsetPos(const K_Math::Vector3& offPos)
{
	K_Math::Vector3 setPos = offPos + relativePos;
	SetPos(setPos);
}


//体力を設定する
void Enemy::SetLife(int life, bool isTakeDamage)
{
	gameObject.GetLife() = life;
	if (isTakeDamage)
	{
		invalidTime.ResetCntTime();
		if (gameObject.GetLife() > 0)
		{
			gameObject.SetState(Status::State::Invalid);
		}
	}
}
//体力を取得する
const int& Enemy::GetLife()
{
	return gameObject.GetLife();
}