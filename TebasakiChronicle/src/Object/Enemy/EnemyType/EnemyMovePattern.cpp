#include "EnemyMovePattern.h"

//コンストラクタ
EnemyMovePattern::EnemyMovePattern(int* moveNum,		//動作番号を入れた配列のアドレス値
	int* skillId,		//動作中に取得可能なスキル番号
	int* durationTime,	//動作の継続時間を入れた配列のアドレス値
	K_Math::Box2D*	src,	//アニメーション画像の最初の位置
	int*			sheet,	//アニメーション枚数
	float*			spd,	//アニメーション速度
	bool*			ir,		//ループするか否か
	int				totalMoveNum,		//動作の総数
	int				transitionNum)		//動作パターン遷移条件の番号
{
	for (int i = 0; i < totalMoveNum; ++i)
	{
		SetMoveAndTime(*(moveNum + i), *(skillId + i), *(durationTime + i));
		animChip.emplace_back(new AnimationCharaChip(*(src + i), *(sheet + i), *(spd + i), *(ir + i)));
	}
	SetTransition(transitionNum);
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

	delete emt;
}

//-----------------------------------------------------------------------------
//動作を行い、現在取得可能なスキルの番号を返す
int EnemyMovePattern::EMove(int& nowMoveOrder, int& timeCnt, CollisionManager& colmanager, Status& status, Move& move, bool& endMovePattern)
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
	++timeCnt;

	mp[nowMoveOrder]->em->EMove(colmanager, status, move);
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
	}
}

//-----------------------------------------------------------------------------
//動作パターン遷移条件を設定する
void EnemyMovePattern::SetTransition(int transitionNum)
{
	switch (transitionNum)
	{
	case 0:	//遷移なし
		emt = new ETransition_Default();
		break;

	case 1: //視界内にプレイヤーが入っているとき
		emt = new ETransition_PIntoView();
		break;

	case 2: //視界内に入っているプレイヤーが自身の反対方向に移動したとき
		emt = new ETransition_PMoveOtherSide();
		break;
	}
}