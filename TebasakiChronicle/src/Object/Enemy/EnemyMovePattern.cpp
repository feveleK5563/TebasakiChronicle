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
//動作を行う
void EnemyMovePattern::Move(int& nowMoveOrder, int& timeCnt, K_Math::Vector3& moveVec)
{
	mp[nowMoveOrder]->em->Move(moveVec);

	++timeCnt;
	//timeCntがmoveTimeMaxを超えたら、次の動作に移行する
	if (timeCnt >= mp[nowMoveOrder]->moveTimeMax)
	{
		timeCnt = 0;

		++nowMoveOrder;
		if (nowMoveOrder >= (int)mp.size())
			nowMoveOrder = 0;
	}
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

	case 1:		//右方向に歩く
		mp.back()->em = new EMove_WalkRight();
		break;

	case 2:		//上に移動する
		mp.back()->em = new EMove_Up();
		break;

	case 3:		//下に移動する
		mp.back()->em = new EMove_Down();
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
	}
}