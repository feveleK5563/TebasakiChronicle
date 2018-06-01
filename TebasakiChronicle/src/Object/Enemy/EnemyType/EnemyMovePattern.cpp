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
		emt.emplace_back(new EnemyMoveTransition(*(msud.transitionIdArr + i)));
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
//動作を行い、現在取得可能なスキルの番号を返す
int EnemyMovePattern::EMove(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, Status& status, Move& move, bool& endMovePattern)
{
	endMovePattern = false;
	//timeCntがmoveTimeMaxを超えたら、次の動作に移行する
	if (timeCnt.IsTimeEnd())
	{
		//終了時の処理
		mp[nowMoveOrder]->em.Finalize(tempmanager, status, move);
		timeCnt.ResetCntTime();

		++nowMoveOrder;
		if (nowMoveOrder >= (int)mp.size())
		{
			nowMoveOrder = 0;
			endMovePattern = true;
		}
	}

	if (timeCnt.GetNowCntTime() == 0)	//最初に行う処理
	{
		timeCnt.SetEndTime(mp[nowMoveOrder]->moveTimeMax);
		mp[nowMoveOrder]->em.Initialize(tempmanager, status, move);
	}
	
	// 動作
	mp[nowMoveOrder]->em.Action(tempmanager, status, move);

	timeCnt.Run();
	return mp[nowMoveOrder]->behaviorId;
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