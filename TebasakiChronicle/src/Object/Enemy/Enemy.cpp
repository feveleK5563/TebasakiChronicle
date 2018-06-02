#include "Enemy.h"
#include "../../Helper.h"

//コンストラクタ
Enemy::Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum) :
	behaviorId(0),
	nowMoveOrder(0),
	nowPatternOrder(0),
	beforeMoveOrder(0),
	beforePatternOrder(0)
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
	gameObject.GetStatus().SetStatusData(	Status::State::Active,
											setPos,
											K_Math::Vector3(0, 0, 0),
											K_Math::Vector3(1, 1, 1),
											direction,
											cpyet->GetHitDamage(),
											cpyet->GetMaxLife());
	if (cpyet->GetIsUseGravity() == false)
	{
		gameObject.GetMove().SetGravity(0.f);
	}

	gameObject.GetMove().SetAddVec(cpyet->GetMoveSpeed());
	gameObject.GetMove().SetJumpPow(cpyet->GetJumpPower());

	//アニメーションと表示画像の設定
	gameObject.SetImage(cpyet->GetTexture(), false);
	gameObject.GetImage().ChangeAnimationPattern(nowMoveOrder);
	gameObject.GetImage().ChangeCharaChip(ems->GetNowAnimChip(nowPatternOrder));

	//コリジョンの設定
	collisionManager.SetBaseCollisionData(cpyet->CreateAndGetBaseCollisionData(), setPos);	//ベースコリジョン
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetRecieveDamageCollisionData());	//0 被ダメージ用コリジョン
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetFieldofviewCollisionData());	//1 視界用コリジョン
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
	SetTugData();
}

//-----------------------------------------------------------------------------
//更新
bool Enemy::Update()
{
	//移動量をゼロクリア
	gameObject.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);

	//重力を加算する
	gameObject.GetMove().GravityOperation(collisionManager.GetConflictionObjectsTag(3).size() > 0);

	//設定されている動作を行う
	ems->EMove(nowMoveOrder, nowPatternOrder, timeCnt, collisionManager, tempCollisionManager, gameObject.GetStatus(), gameObject.GetMove());

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
	tag = collisionManager.GetConflictionObjectsTag(EnemyCollisionName::RecieveDamage);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			gameObject.GetStatus().GetLife() -= ((Status*)it->userData)->GetAttackPoint();
		}
	}
	int hp = gameObject.GetStatus().GetLife();

	//カメラを受ける
	tag = collisionManager.GetConflictionObjectsTag(EnemyCollisionName::RecieveCameraGan);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			//カメラガンから受ける影響をここに書きなされ

		}
	}

	return gameObject.GetStatus().GetLife() <= 0;
}

//-----------------------------------------------------------------------------
//タグに情報を格納
void Enemy::SetTugData()
{
	skillAndChip->nowCharaChip = gameObject.GetImage().GetNowAnimationCharaChip();
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
		gameObject.GetImage().ChangeCharaChip(ems->GetNowAnimChip(nowPatternOrder));
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