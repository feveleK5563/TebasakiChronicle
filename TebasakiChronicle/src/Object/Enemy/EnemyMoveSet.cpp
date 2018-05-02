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
void EnemyMoveSet::CreateMotionPattern(	int* moveNum,		//動作番号を入れた配列のアドレス値
										int* skillId,		//動作中に取得可能なスキル番号
										int* durationTime,	//動作の継続時間を入れた配列のアドレス値
										K_Math::Box2D*	src,	//アニメーション画像の最初の位置
										int*			sheet,	//アニメーション枚数
										float*			spd,	//アニメーション速度
										bool*			ir,		//ループするか否か
										int				totalMoveNum,		//動作の総数
										int				transitionNum)		//動作パターンの遷移条件の番号
{
	empattern.emplace_back(new EnemyMovePattern(moveNum, skillId, durationTime, src, sheet, spd, ir, totalMoveNum, transitionNum));
}

//-----------------------------------------------------------------------------
//指定パターン番号のアニメーションを返す
const std::vector<AnimationCharaChip*> EnemyMoveSet::GetNowAnimChip(int nowPatternOrder)
{
	return empattern[nowPatternOrder]->animChip;
}

//-----------------------------------------------------------------------------
//現在の動作パターンを実行し、現在取得可能なスキル番号を返す
int EnemyMoveSet::Move(int& nowMoveOrder, int& nowPatternOrder, int& timeCnt, K_Math::Vector3& moveVec)
{
	//パターンの遷移条件を満たしたら即パターン変更
	for (int i = 0; i < (int)empattern.size(); ++i)
	{
		if (nowPatternOrder != i && 
			empattern[i]->emt->Transition())
		{
			PatternTransition(nowMoveOrder, nowPatternOrder, timeCnt, i);
			break;
		}
	}
	return empattern[nowPatternOrder]->Move(nowMoveOrder, timeCnt, moveVec);
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