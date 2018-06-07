#include "SkillType.h"

//�R���X�g���N�^
//!@brief �R���X�g���N�^
//!@param[in] �ő�g�p��
//!@param[in] �o������
//!@param[in] �p������
SkillType::SkillType(const int& moveID,const int& maxUseNum, const float& appearDist, const int& continueTime,const int& attackPoint)
	: maxUseNum(maxUseNum), appearDist(appearDist), continueTime(continueTime)
	, charaBehaivor(moveID), attackPoint(attackPoint)
{
	
}


//-----------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------
SkillType::~SkillType()
{

}



//-----------------------------------------------------------
//�X�V����
//-----------------------------------------------------------
void	SkillType::UpDate(GameObject& object)
{
	
}

//������
void	SkillType::BehaivorInit(TemporaryCollisionManager& tempCol, Status& status, Move& move)
{
	charaBehaivor.Initialize(tempCol, status, move);
}
//�I��
void	SkillType::BehaivorFinal(TemporaryCollisionManager& tempCol, Status& status, Move& move)
{
	charaBehaivor.Finalize(tempCol, status, move);
}
void	SkillType::Behaivor(TemporaryCollisionManager& tempCol, Status& status, Move& move)
{
	charaBehaivor.Action(tempCol, status, move);
}



//�擾����
int		SkillType::GetContinueTime() const
{
	return continueTime;
}
float	SkillType::GetAppearDist() const
{
	return appearDist;
}
int		SkillType::GetMaxUseNum() const
{
	return maxUseNum;
}
int		SkillType::GetAttackPoint() const
{
	return attackPoint;
}


//!@brief	�X�L���̃^�C�v(�n��)��Ԃ�
//!@return	�X�L���̃^�C�v
SkillType::Type&	SkillType::GetType()
{
	return type;
}

//!@brief	�^����R���W�����}�X�N��Ԃ�
//!@return	�^����R���W�����}�X�N
Status::CollisionMaskState&	SkillType::GetGiveCollisionMask()
{
	return giveCollisionMask;
}

//!@brief	�󂯎��R���W�����}�X�N��Ԃ�
//!@return	�󂯎��R���W�����}�X�N
Status::CollisionMaskState&	SkillType::GetReciveCollisionMask()
{
	return reciveCollisionMask;
}