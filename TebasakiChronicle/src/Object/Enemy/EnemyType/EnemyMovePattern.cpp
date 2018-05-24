#include "EnemyMovePattern.h"

//コンストラクタ
EnemyMovePattern::EnemyMovePattern(const MoveSetUpData& msud)
{
	for (int i = 0; i < msud.totalMoveNum; ++i)
	{
		SetMoveAndTime(*(msud.moveIdArr + i), *(msud.behaviorIdArr + i), *(msud.durationTimeArr + i));
		animChip.emplace_back(new AnimationCharaChip(*(msud.srcArr + i), *(msud.sheetArr + i), *(msud.spdArr + i), *(msud.isRoopArr + i), *(msud.basisPosArr + i)));
	}
	for (int i = 0; i < msud.patternNum; ++i)
	{
		SetTransition(*(msud.transitionIdArr + i));
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
	return mp[nowMoveOrder]->behaviorId;
}

//-----------------------------------------------------------------------------
//動作順をリセットする
void EnemyMovePattern::MoveReset(int& nowMoveOrder)
{
	nowMoveOrder = 0;
}

//-----------------------------------------------------------------------------
//動作を設定する
void EnemyMovePattern::SetMoveAndTime(int moveNum, int behaviorId, int durationTime)
{
	mp.emplace_back(new MovePattern(behaviorId, durationTime));
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
	switch (abs(transitionNum))
	{
	case 0:	//遷移しない
		emt.emplace_back(new EnemyMoveTransition(new ETransition_NotTransition(), transitionNum));
		break;

	case 1: //一連の動作が終了したとき
		emt.emplace_back(new EnemyMoveTransition(new ETransition_EndMovePattern(), transitionNum));
		break;

	case 2: //視界内にプレイヤーが入っているとき
		emt.emplace_back(new EnemyMoveTransition(new ETransition_PlayerIntoVisibility(), transitionNum));
		break;
	}
}

//-----------------------------------------------------------------------------
//アニメーションのキャラチップを返す
const std::vector<AnimationCharaChip*>&  EnemyMovePattern::GetNowAnimChip()
{
	return animChip;
}

//-----------------------------------------------------------------------------
//指定番号の遷移条件を実行し、クリアしたらtrueを返す
bool EnemyMovePattern::IsTransition(int num, CollisionManager& colmanager, Status& status, const bool endMovePattern)
{
	return emt[num]->IsTransition(colmanager, status, endMovePattern);
}