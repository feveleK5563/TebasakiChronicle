#include "EnemyMoveTransition.h"

EnemyMoveTransitionAbstract::~EnemyMoveTransitionAbstract(){}

EnemyMoveTransition::EnemyMoveTransition(int transitionNum) :
	isReturnTrue(transitionNum >= 0)
{
	SetTransition(transitionNum);
}
EnemyMoveTransition::~EnemyMoveTransition()
{
	delete transition;
}

//-----------------------------------------------------------------------------
//����p�^�[���J�ڏ�����ݒ肷��
void EnemyMoveTransition::SetTransition(int transitionNum)
{
	switch (abs(transitionNum))
	{
	case 0:	//�J�ڂ��Ȃ�
		transition = new ETransition_NotTransition();
		break;

	case 1: //��A�̓��삪�I�������Ƃ�
		transition = new ETransition_EndMovePattern();
		break;

	case 2: //���E���Ƀv���C���[�������Ă���Ƃ�
		transition = new ETransition_PlayerIntoVisibility();
		break;

	case 3:	//�U���J�ڗp�R���W�����Ƀv���C���[�������Ă���Ƃ�
		transition = new ETransition_PlayerIntoAttackArea();
	}
}
//-----------------------------------------------
//�J�ڏ������N���A������true��Ԃ�
bool EnemyMoveTransition::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	return transition->IsTransition(cm, status, endMovePattern) == isReturnTrue;
}

//-----------------------------------------------------------------------------
//0�F�J�ڂ��Ȃ�
bool ETransition_NotTransition::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	return false;
}

//-----------------------------------------------------------------------------
//1�F��A�̓��삪�I�������Ƃ�
bool ETransition_EndMovePattern::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (endMovePattern == true)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//2�F���E���Ƀv���C���[�������Ă���Ƃ�
bool ETransition_PlayerIntoVisibility::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(1))
		return true;

	return false;
}

//-----------------------------------------------
//3�F�U���J�ڗp�R���W�����Ƀv���C���[�������Ă���Ƃ�
bool ETransition_PlayerIntoAttackArea::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(2))
		return true;

	return false;
}