#include "Enemy.h"

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
	delete eController;
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
	skillAndChip.pos = &gameObject.GetStatus().GetPos();
	skillAndChip.textureName = &gameObject.GetImage().GetTextureName();
	skillAndChip.skillId = &eController->GetSkillId();
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
	gameObject.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);
	eController->EMove(nowMoveOrder, nowPatternOrder, collisionManager, gameObject.GetStatus(), gameObject.GetMove());

	AnimationUpdate();

	//コリジョンを動かす
	collisionManager.MoveBaseCollision(gameObject.GetMove().GetMoveVec(), gameObject.GetStatus().GetDirection(), true);
	gameObject.GetPos() = collisionManager.GetBaseCollisionObjectPosition();

	SetTugData();

	return false;
}

//-----------------------------------------------------------------------------
//タグ情報を格納
void Enemy::SetTugData()
{
	skillAndChip.nowCharaChip = gameObject.GetImage().GetNowAnimationCharaChip();
	collisionManager.SetSubCollisionTug(5, &skillAndChip);
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
void Enemy::Draw()
{
	gameObject.GetImage().ImageDraw3D(	gameObject.GetStatus().GetPos(),
										gameObject.GetStatus().GetAngle(),
										gameObject.GetStatus().GetScale(),
										gameObject.GetStatus().GetDirection());
}