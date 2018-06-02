#include "EnemyController.h"

//�R���X�g���N�^
EnemyController::EnemyController(EnemyMoveSet* cpyems) :
	ems(cpyems),
	behaviorId(0) {}

//�f�X�g���N�^
EnemyController::~EnemyController(){}

//-----------------------------------------------------------------------------
//�X�L���ԍ����擾
int& EnemyController::GetBehaviorId()
{
	return behaviorId;
}

//-----------------------------------------------------------------------------
//����̎��s
void EnemyController::EMove(int& nowMoveOrder, int& nowPatternOrder, CollisionManager& cm, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	behaviorId = ems->EMove(nowMoveOrder, nowPatternOrder, timeCnt, cm, tempmanager, status, move);
}

//-----------------------------------------------------------------------------
//EnemyMoveSet����L�����`�b�v���擾
const std::vector<AnimationCharaChip*> EnemyController::GetNowCharaChip(int nowPatternOrder)
{
	return ems->GetNowAnimChip(nowPatternOrder);
}