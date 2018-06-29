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

	case 4:	//�������n�`�ƐڐG���Ă���Ƃ�
		transition = new ETransition_HitFoot();
		break;

	case 5: //���E���̃v���C���[�������Ă�������ɂ���Ƃ�
		transition = new ETransition_IntoVisibilityAndMatchDirection();
		break;
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

//-----------------------------------------------
//4�F�������n�`�ƐڐG���Ă���Ƃ�
bool ETransition_HitFoot::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(3))
		return true;

	return false;
}

//-----------------------------------------------
//5�F���E���̃v���C���[�������Ă�������ɂ���Ƃ�
bool ETransition_IntoVisibilityAndMatchDirection::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	auto pdata = cm.GetConflictionObjectsTag(1);
	if (pdata.size() <= 0)
		return false;

	if ((((Status*)pdata[0])->GetPos().x < status.GetPos().x && status.GetDirection() == Status::Direction::Left) ||
		(((Status*)pdata[0])->GetPos().x > status.GetPos().x && status.GetDirection() == Status::Direction::Right))
	{
		return true;
	}
	return false;
}