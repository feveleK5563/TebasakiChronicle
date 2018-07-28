#include "EnemyMovePattern.h"

//コンストラクタ
EnemyMovePattern::EnemyMovePattern(const MoveSetUpData& msud)
{
	for (int i = 0; i < msud.totalMoveNum; ++i)
	{
		mp.emplace_back(new MovePattern(*(msud.moveIdArr + i), *(msud.behaviorIdArr + i), *(msud.durationTimeArr + i)));
		animChip.emplace_back(new AnimationCharaChip(*(msud.srcArr + i), *(msud.sheetArr + i), *(msud.spdArr + i), *(msud.isRoopArr + i), *(msud.basisPosArr + i)));
	}
	for (int i = 0; i < msud.patternNum; ++i)
	{
		int hoge = *(msud.transitionIdArr + i);
		emt.emplace_back(new EnemyMoveTransition(hoge));
	}
}

//デストラクタ
EnemyMovePattern::~EnemyMovePattern()
{ 
	for (auto it : mp)
	{
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
//動作が終了したか否かを返す
bool EnemyMovePattern::IsEndMovePattern(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//timeCntがmoveTimeMaxを超えたら、次の動作に移行する
	if (timeCnt.IsTimeEnd())
	{
		//終了時の処理
		EMoveEnd(nowMoveOrder, timeCnt, tempmanager, status, move);

		++nowMoveOrder;
		if (nowMoveOrder >= (int)mp.size())
		{
			nowMoveOrder = 0;
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//動作を行い、現在取得可能なスキルの番号を返す
int EnemyMovePattern::EMove(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	if (timeCnt.GetNowCntTime() == 0)	//最初に行う処理
	{
		timeCnt.SetEndTime(mp[nowMoveOrder]->moveTimeMax);
		mp[nowMoveOrder]->em.Initialize(tempmanager, status, move, timeCnt);
	}

	// 動作
	mp[nowMoveOrder]->em.Action(tempmanager, status, move, timeCnt);

	timeCnt.Run();
	return mp[nowMoveOrder]->behaviorId;
}

//-----------------------------------------------------------------------------
//終了時の処理を行う
void EnemyMovePattern::EMoveEnd(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	mp[nowMoveOrder]->em.Finalize(tempmanager, status, move);
	timeCnt.ResetCntTime();
}

//-----------------------------------------------------------------------------
//動作順をリセットする
void EnemyMovePattern::MoveReset(int& nowMoveOrder)
{
	nowMoveOrder = 0;
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