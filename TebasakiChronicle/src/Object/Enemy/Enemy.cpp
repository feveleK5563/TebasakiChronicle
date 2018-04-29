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
	delete imgManager;
}

//-----------------------------------------------------------------------------
//敵情報を設定
void Enemy::SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos)
{
	eController = new EnemyController(cpyet->emSet);
	life = cpyet->maxLife;
	pos = setPos;
	angle = { 0, 0, 0 };
	scale = { 1, 1, 1 };
	moveVec = { 0, 0, 0 };
	cData = CM::CreateCollisionObject(cpyet->cShape, true, 1, pos, angle);
	imgManager = new ImageManager(cpyet->texture, false);
	imgManager->ChangeAnimationPattern(nowMoveOrder);
	imgManager->ChangeCharaChip(eController->GetNowCharaChip(nowPatternOrder));
}

//-----------------------------------------------------------------------------
//更新
void Enemy::Update()
{
	moveVec = { 0, 0, 0 };	//この処理はコリジョンで行う

	eController->Move(nowMoveOrder, nowPatternOrder, moveVec);
	imgManager->Animation();

	//現在の動作と前の動作が異なる場合アニメーションパターンを変更する
	if (beforeMoveOrder != nowMoveOrder)
	{
		imgManager->ChangeAnimationPattern(nowMoveOrder);
	}
	beforeMoveOrder = nowMoveOrder;

	//現在の動作パターンと前のパターンが異なる場合キャラチップを変更する
	if (beforePatternOrder != nowPatternOrder)
	{
		imgManager->ChangeCharaChip(eController->GetNowCharaChip(nowPatternOrder));
	}
	beforePatternOrder = nowPatternOrder;

	pos += moveVec; //この処理はコリジョンで行う
}

//-----------------------------------------------------------------------------
//描画
void Enemy::Draw()
{
	imgManager->ImageDraw3D(pos, angle, scale);
}