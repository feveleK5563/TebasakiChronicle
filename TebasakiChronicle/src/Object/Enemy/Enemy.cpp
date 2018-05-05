#include "Enemy.h"

//コンストラクタ
Enemy::Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos) :
	nowMoveOrder(0),
	nowPatternOrder(0),
	beforeMoveOrder(0),
	beforePatternOrder(0)
{
	SetEnemyType(cpyet, setPos);
}

//デストラクタ
Enemy::~Enemy()
{
	delete eController;
}

//-----------------------------------------------------------------------------
//敵情報を設定
void Enemy::SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos)
{
	eController = new EnemyController(cpyet->GetEnemyMoveSet());
	//gameObject.GetStatus()->GetLife() = cpyet->GetMaxLife();
	gameObject.GetStatus()->SetStatusData(	Status::State::Walk,
											setPos,
											K_Math::Vector3(0, 0, 0),
											K_Math::Vector3(1, 1, 1),
											Status::Direction::Right,
											cpyet->GetHitDamage());

	//アニメーションと表示画像の設定
	ImageManager* im = gameObject.GetImage();
	im = new ImageManager(cpyet->GetTextureName(), cpyet->GetTexture(), false);
	im->ChangeAnimationPattern(nowMoveOrder);
	im->ChangeCharaChip(eController->GetNowCharaChip(nowPatternOrder));

	//コリジョンの設定
	collisionManager.SetBaseCollisionData(cpyet->GetBaseCollisionData());			//ベースコリジョン
	collisionManager.SetSubCollisionData(cpyet->GetRecieveDamageCollisionData());	//被ダメージ用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetFieldofviewCollisionData());		//視界用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetAttackAreaCollisionData());		//攻撃動作遷移用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetCheckFootCollisionData());		//足元判定用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetCheckHeadCollisionData());		//頭上判定用コリジョン
	collisionManager.SetSubCollisionData(cpyet->GetRecieveCameraCollisionData());	//被カメラガン用コリジョン

	//タグの設定
	skillAndChip.pos = &gameObject.GetStatus()->GetPos();
	skillAndChip.textureName = &gameObject.GetImage()->GetTextureName();
	skillAndChip.skillId = &eController->GetSkillId();
	SetTugData();
}

//-----------------------------------------------------------------------------
//更新
void Enemy::Update()
{
	K_Math::Vector3 moveVec = { 0, 0, 0 };	//※moveVecはStatusクラスのメンバ変数

	//eController->Move(nowMoveOrder, nowPatternOrder, moveVec);

	AnimationUpdate();

	collisionManager.MoveBaseCollision(moveVec, gameObject.GetStatus()->GetDirection(), true);

	SetTugData();
}

//-----------------------------------------------------------------------------
//タグ情報を格納
void Enemy::SetTugData()
{
	skillAndChip.nowCharaChip = gameObject.GetImage()->GetNowAnimationCharaChip();

	for (int i = 0; i < 5; ++i)
	{
		collisionManager.SetSubCollisionTug(i, gameObject.GetStatus());
	}
	collisionManager.SetSubCollisionTug(5, &skillAndChip);
}

//-----------------------------------------------------------------------------
//描画、アニメーションの更新
void Enemy::AnimationUpdate()
{
	gameObject.GetImage()->Animation();

	//現在の動作と前の動作が異なる場合アニメーションパターンを変更する
	if (beforeMoveOrder != nowMoveOrder)
	{
		gameObject.GetImage()->ChangeAnimationPattern(nowMoveOrder);
	}
	beforeMoveOrder = nowMoveOrder;

	//現在の動作パターンと前のパターンが異なる場合キャラチップを変更する
	if (beforePatternOrder != nowPatternOrder)
	{
		gameObject.GetImage()->ChangeCharaChip(eController->GetNowCharaChip(nowPatternOrder));
	}
	beforePatternOrder = nowPatternOrder;
}

//-----------------------------------------------------------------------------
//描画
void Enemy::Draw()
{
	gameObject.GetImage()->ImageDraw3D(	gameObject.GetStatus()->GetPos(),
										gameObject.GetStatus()->GetAngle(),
										gameObject.GetStatus()->GetScale());
}