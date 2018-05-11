#include "Enemy.h"
#include "../../Helper.h"

//コンストラクタ
Enemy::Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction) :
	nowMoveOrder(0),
	nowPatternOrder(0),
	beforeMoveOrder(0),
	beforePatternOrder(0)
{
	SetEnemyType(cpyet, setPos, direction);
}

//デストラクタ
Enemy::~Enemy()
{
	Memory::SafeDelete(eController);
	Memory::SafeDelete(skillAndChip);
}

//-----------------------------------------------------------------------------
//敵情報を設定
void Enemy::SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction)
{
	eController = new EnemyController(cpyet->GetEnemyMoveSet());
	gameObject.GetStatus().SetStatusData(	Status::State::Active,
											setPos,
											K_Math::Vector3(0, 0, 0),
											K_Math::Vector3(1, 1, 1),
											direction,
											cpyet->GetHitDamage(),
											cpyet->GetMaxLife());

	gameObject.GetMove().SetAddVec(cpyet->GetMoveSpeed());
	gameObject.GetMove().SetJumpPow(cpyet->GetJumpPower());

	//アニメーションと表示画像の設定
	gameObject.SetImage(cpyet->GetTextureName(), cpyet->GetTexture(), false);
	gameObject.GetImage().ChangeAnimationPattern(nowMoveOrder);
	gameObject.GetImage().ChangeCharaChip(eController->GetNowCharaChip(nowPatternOrder));

	//コリジョンの設定
	collisionManager.SetBaseCollisionData(cpyet->GetBaseCollisionData(), setPos);	//ベースコリジョン
	collisionManager.SetSubCollisionData(cpyet->GetRecieveDamageCollisionData());	//0 被ダメージ用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetFieldofviewCollisionData());		//1 視界用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetAttackAreaCollisionData());		//2 攻撃動作遷移用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetCheckFootCollisionData());		//3 足元判定用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetCheckHeadCollisionData());		//4 頭上判定用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetRecieveCameraCollisionData());	//5 被カメラガン用コリジョン

	//タグの設定
	skillAndChip = new SkillAndCharaChip();
	skillAndChip->pos = &gameObject.GetStatus().GetPos();
	skillAndChip->textureName = &gameObject.GetImage().GetTextureName();
	skillAndChip->skillId = &eController->GetSkillId();
	for (int i = 0; i < 5; ++i)
	{
		collisionManager.SetSubCollisionTug(i, &gameObject.GetStatus());
	}
	SetTugData();
}

//-----------------------------------------------------------------------------
//更新
bool Enemy::Update()
{
	//移動量をゼロクリア
	gameObject.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);

	//重力を加算する
	gameObject.GetMove().GravityOperation(collisionManager.GetConflictionObjectsUserData(3).size() > 0);

	//設定されている動作を行う
	eController->EMove(nowMoveOrder, nowPatternOrder, collisionManager, tempCollisionManager, gameObject.GetStatus(), gameObject.GetMove());

	//アニメーションの更新
	AnimationUpdate();

	//コリジョンを動かす
	collisionManager.MoveBaseCollision(gameObject.GetMove().GetMoveVec(), gameObject.GetStatus().GetDirection(), true);
	gameObject.GetPos() = collisionManager.GetBaseCollisionObjectPosition();
	tempCollisionManager.Update();
	//タグ情報を更新
	SetTugData();

	return RecieveCollisionOperation();
}

//-----------------------------------------------------------------------------
//コリジョンとの接触処理
//被ダメージによって体力が0になったらtrueを返す
bool Enemy::RecieveCollisionOperation()
{
	std::vector<K_Physics::CollisionTag*> tag;

	//ダメージを受ける
	tag = collisionManager.GetConflictionObjectsUserData(Enemy::EnemyCollisionName::RecieveDamage);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			gameObject.GetStatus().GetLife() -= ((Status*)it->userData)->GetAttackPoint();
		}
	}
	int hp = gameObject.GetStatus().GetLife();

	//カメラを受ける
	tag = collisionManager.GetConflictionObjectsUserData(Enemy::EnemyCollisionName::RecieveCameraGan);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			
		}
	}

	return gameObject.GetStatus().GetLife() <= 0;
}

//-----------------------------------------------------------------------------
//タグに情報を格納
void Enemy::SetTugData()
{
	skillAndChip->nowCharaChip = gameObject.GetImage().GetNowAnimationCharaChip();
	collisionManager.SetSubCollisionTug(5, skillAndChip);
}

//-----------------------------------------------------------------------------
//描画、アニメーションの更新
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
		gameObject.GetImage().ChangeCharaChip(eController->GetNowCharaChip(nowPatternOrder));
	}
	beforePatternOrder = nowPatternOrder;
}

//-----------------------------------------------------------------------------
//描画
void Enemy::Render()
{
	gameObject.GetImage().ImageDraw3D(	gameObject.GetStatus().GetPos(),
										gameObject.GetStatus().GetAngle(),
										gameObject.GetStatus().GetScale(),
										gameObject.GetStatus().GetDirection());
	tempCollisionManager.Render();
}