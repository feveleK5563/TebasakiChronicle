#include "SkillType.h"

//�R���X�g���N�^
//!@brief �R���X�g���N�^
//!@param[in] �ő�g�p��
//!@param[in] �o������
//!@param[in] �p������
SkillType::SkillType(const int& moveID,const int& maxUseNum, const float& appearDist, const int& continueTime,const int& attackPoint)
	: maxUseNum(maxUseNum), appearDist(appearDist), continueTime(continueTime)
	, charaBehaivor(new CharacterBehavior(moveID)), attackPoint(attackPoint)
{
	
}


//-----------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------
SkillType::~SkillType()
{
	Memory::SafeDelete(charaBehaivor);
}



//-----------------------------------------------------------
//�X�V����
//-----------------------------------------------------------
void	SkillType::UpDate(GameObject& object)
{
	
}

//������
void	SkillType::BehaivorInit(TemporaryCollisionManager& tempCol, GameObject& gameObject, TimeCount& timeCnt)
{
	charaBehaivor->Initialize(tempCol, gameObject, timeCnt);
}
//�I��
void	SkillType::BehaivorFinal(TemporaryCollisionManager& tempCol, GameObject& gameObject)
{
	charaBehaivor->Finalize(tempCol, gameObject);
}
void	SkillType::Behaivor(TemporaryCollisionManager& tempCol, GameObject& gameObject, CollisionManager* collmanager, TimeCount& timeCnt)
{
	charaBehaivor->Action(tempCol, gameObject, collmanager, timeCnt);
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

