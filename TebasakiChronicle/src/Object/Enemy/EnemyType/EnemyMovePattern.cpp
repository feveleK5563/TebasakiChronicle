#include "EnemyMovePattern.h"

//コンストラクタ
EnemyMovePattern::EnemyMovePattern(	int* moveIdArr,			//動作番号を入れた配列のアドレス値
									int* skillIdArr,		//動作中に取得可能なスキル番号
									int* durationTimeArr,	//動作の継続時間を入れた配列のアドレス値
									K_Math::Box2D*	src,	//アニメーション画像の最初の位置
									int*			sheet,	//アニメーション枚数
									float*			spd,	//アニメーション速度
									bool*			ir,		//ループするか否か
									int*			transitionIdArr,	//他動作パターンへの遷移条件の番号
									int				patternNum,			//動作パターンの総数
									int				totalMoveNum)		//動作の総数
{
	for (int i = 0; i < totalMoveNum; ++i)
	{
		SetMoveAndTime(*(moveIdArr + i), *(skillIdArr + i), *(durationTimeArr + i));
		animChip.emplace_back(new AnimationCharaChip(*(src + i), *(sheet + i), *(spd + i), *(ir + i)));
	}
	for (int i = 0; i < patternNum; ++i)
	{
		SetTransition(*(transitionIdArr + i));
	}
}

//デストラクタ
EnemyMovePattern::~EnemyMovePattern()
{ 
	for (auto it : mp)
	{
		delete it->em;
		delete it;
	}

	for (auto it : animChip)
	{
		delete it;
	}

	for (auto it : emt)
	{
		delete it;
	}
}

//-----------------------------------------------------------------------------
//動作を行い、現在取得可能なスキルの番号を返す
int EnemyMovePattern::EMove(int& nowMoveOrder, int& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, bool& endMovePattern)
{
	endMovePattern = false;
	//timeCntがmoveTimeMaxを超えたら、次の動作に移行する
	if (timeCnt >= mp[nowMoveOrder]->moveTimeMax)
	{
		timeCnt = 0;

		++nowMoveOrder;
		if (nowMoveOrder >= (int)mp.size())
		{
			nowMoveOrder = 0;
			endMovePattern = true;
		}
	}

	if (timeCnt == 0)	//最初に行う動作
	{
		mp[nowMoveOrder]->em->FirstMove(colmanager, tempmanager, status, move);
	}
	else				//通常の動作
	{
		mp[nowMoveOrder]->em->EMove(colmanager, tempmanager, status, move);
	}

	++timeCnt;
	return mp[nowMoveOrder]->skillId;
}

//-----------------------------------------------------------------------------
//動作順をリセットする
void EnemyMovePattern::MoveReset(int& nowMoveOrder)
{
	nowMoveOrder = 0;
}

//-----------------------------------------------------------------------------
//動作を設定する
void EnemyMovePattern::SetMoveAndTime(int moveNum, int skillId, int durationTime)
{
	mp.emplace_back(new MovePattern(skillId, durationTime));
	switch (moveNum)
	{
	case 0:		//何もしない
		mp.back()->em = new EMove_NoMotion();
		break;

	case 1:		//向いている方向に移動する
		mp.back()->em = new EMove_Movement();
		break;

	case 2:		//ジャンプする
		mp.back()->em = new EMove_Jump();
		break;

	case 3:		//前方に攻撃する
		mp.back()->em = new EMove_FrontAttack();
		break;
	}
}

//-----------------------------------------------------------------------------
//動作パターン遷移条件を設定する
void EnemyMovePattern::SetTransition(int transitionNum)
{
	emt.emplace_back();
	switch (transitionNum)
	{
	case 0:	//遷移しない
		emt.back() = new ETransition_NotTrans();
		break;

	case 1: //視界内にプレイヤーが入っているとき
		emt.back() = new ETransition_PIntoView();
		break;

	case 2: //視界内に入っているプレイヤーが自身の反対方向に移動したとき
		emt.back() = new ETransition_PMoveOtherSide();
		break;
	}
}