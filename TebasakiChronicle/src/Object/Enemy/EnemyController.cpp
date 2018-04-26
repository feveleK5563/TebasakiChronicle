#include "EnemyController.h"

//コンストラクタ
EnemyController::EnemyController(EnemyMoveSet* cpyems) :
	ems(cpyems),
	skillId(0),
	timeCnt(0) {}

//デストラクタ
EnemyController::~EnemyController(){}

//-----------------------------------------------------------------------------
//動作の実行
void EnemyController::Move(int& nowMoveOrder, int& nowPatternOrder, K_Math::Vector3& moveVec)
{
	ems->Move(nowMoveOrder, nowPatternOrder, timeCnt, moveVec);
}

//-----------------------------------------------------------------------------
//EnemyMoveSetからキャラチップを取得
const std::vector<AnimationCharaChip*> EnemyController::GetNowCharaChip(int nowPatternOrder)
{
	return ems->empattern[nowPatternOrder]->animChip;
}