#include "EnemyController.h"

//コンストラクタ
EnemyController::EnemyController(EnemyMoveSet* cpyems) :
	ems(cpyems),
	skillId(0) {}

//デストラクタ
EnemyController::~EnemyController(){}

//-----------------------------------------------------------------------------
//スキル番号を取得
int& EnemyController::GetSkillId()
{
	return skillId;
}

//-----------------------------------------------------------------------------
//動作の実行
void EnemyController::EMove(int& nowMoveOrder, int& nowPatternOrder, CollisionManager& cm, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	ems->EMove(nowMoveOrder, nowPatternOrder, timeCnt, cm, tempmanager, status, move);
}

//-----------------------------------------------------------------------------
//EnemyMoveSetからキャラチップを取得
const std::vector<AnimationCharaChip*> EnemyController::GetNowCharaChip(int nowPatternOrder)
{
	return ems->GetNowAnimChip(nowPatternOrder);
}