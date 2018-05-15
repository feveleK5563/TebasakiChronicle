#include "SkillType.h"


//-----------------------------------------------------------
//�R���X�g���N�^
//-----------------------------------------------------------
SkillType::SkillType(const int& continueTime_, const float& distance_,
	GameObject& obj,const std::string& textureName,const AnimationCharaChip& animCharaChip)
	: continueTime(continueTime_), distance(distance_),appearPos(obj.GetPos())
{
	skillObject = new SkillObject(obj,distance,textureName,animCharaChip);
	std::cout << "SkillObject�𐶐����܂���" << std::endl;
}

//-----------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------
SkillType::~SkillType()
{
	if (skillObject != nullptr)
	{
		delete skillObject;
		skillObject = nullptr;
		std::cout << "SkillObject���������܂���" << std::endl;
	}
}



//-----------------------------------------------------------
//�X�V����
//-----------------------------------------------------------
void	SkillType::UpDate()
{

}

//-----------------------------------------------------------
//�`�揈��
//-----------------------------------------------------------
void	SkillType::Render()
{

}

