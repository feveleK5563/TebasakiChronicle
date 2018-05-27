#include "EnemyMoveSet.h"

//コンストラクタ
EnemyMoveSet::EnemyMoveSet() {}

//デストラクタ
EnemyMoveSet::~EnemyMoveSet()
{
	for (auto it : empattern)
		delete it;
}

//-----------------------------------------------------------------------------
//動作パターン集合の生成
void EnemyMoveSet::CreateMotionPattern(EnemyMovePattern::MoveSetUpData& msud)
{
	empattern.emplace_back(new EnemyMovePattern(msud));
}

//-----------------------------------------------------------------------------
//指定パターン番号のアニメーションを返す
const std::vector<AnimationCharaChip*>& EnemyMoveSet::GetNowAnimChip(int nowPatternOrder)
{
	return empattern[nowPatternOrder]->GetNowAnimChip();
}

//-----------------------------------------------------------------------------
//現在の動作パターンを実行し、現在プレイヤーが取得可能なスキル番号を返す
int EnemyMoveSet::EMove(int& nowMoveOrder, int& nowPatternOrder, TimeCount& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	bool endMovePattern = false;	//動作パターンが一巡したか(最後までいったか)どうかを格納
	int behaviorId = empattern[nowPatternOrder]->EMove(nowMoveOrder, timeCnt, colmanager, tempmanager, status, move, endMovePattern);

	//パターンの遷移条件を満たしていたらパターン変更
	for (int i = 0; i < (int)empattern.size(); ++i)
	{
		if (i != nowPatternOrder &&
			empattern[nowPatternOrder]->IsTransition(i, colmanager, status, endMovePattern))
		{
			PatternTransition(nowMoveOrder, nowPatternOrder, timeCnt, i);
			break;
		}
	}

	return behaviorId;
}

//-----------------------------------------------------------------------------
//動作パターンを指定番号に遷移させる
void EnemyMoveSet::PatternTransition(int& nowMoveOrder, int& nowPatternOrder, TimeCount& timeCnt, int patternNum)
{
	if (patternNum >= (int)empattern.size())
		return;

	empattern[nowPatternOrder]->MoveReset(nowMoveOrder);
	nowPatternOrder = patternNum;
	timeCnt.ResetCntTime();
}