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
void EnemyMoveSet::CreateMotionPattern( int* moveIdArr,			//動作番号を入れた配列のアドレス値
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
	empattern.emplace_back(new EnemyMovePattern(moveIdArr, skillIdArr, durationTimeArr, src, sheet, spd, ir, transitionIdArr, patternNum, totalMoveNum));
}

//-----------------------------------------------------------------------------
//指定パターン番号のアニメーションを返す
const std::vector<AnimationCharaChip*> EnemyMoveSet::GetNowAnimChip(int nowPatternOrder)
{
	return empattern[nowPatternOrder]->animChip;
}

//-----------------------------------------------------------------------------
//現在の動作パターンを実行し、現在プレイヤーが取得可能なスキル番号を返す
int EnemyMoveSet::EMove(int& nowMoveOrder, int& nowPatternOrder, int& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	bool endMovePattern = false;	//動作パターンが一巡したか(最後までいったか)どうかを格納
	int idNum = empattern[nowPatternOrder]->EMove(nowMoveOrder, timeCnt, colmanager, tempmanager, status, move, endMovePattern);

	//パターンの遷移条件を満たしていたらパターン変更
	for (int i = 0; i < (int)empattern.size(); ++i)
	{
		if (empattern[nowPatternOrder]->emt[i]->Transition(colmanager, status))
		{
			PatternTransition(nowMoveOrder, nowPatternOrder, timeCnt, i);
			break;
		}
	}

	return idNum;
}

//-----------------------------------------------------------------------------
//動作パターンを指定番号に遷移させる
void EnemyMoveSet::PatternTransition(int& nowMoveOrder, int& nowPatternOrder, int& timeCnt, int patternNum)
{
	if (patternNum >= (int)empattern.size())
		return;

	empattern[nowPatternOrder]->MoveReset(nowMoveOrder);
	nowPatternOrder = patternNum;
	timeCnt = 0;
}