#pragma once
#include "../src/Object/Player/Skill/SkillType.h"

//---------------------------------------------------------------
//�X�L���\�[�h
//�T�v:�؂�X�L���𔭓�
//�����:�����
//---------------------------------------------------------------
class SkillSword : public SkillType
{
public:
	//!@brief �R���X�g���N�^
	//!@param[in] continueTime_ �p������
	//!@param[in] distance_ ����
	//!@param[in] appearPos_ �o���ʒu
	explicit SkillSword(const int& continueTime_, const float& distance_,
		GameObject& obj,const std::string& textureName,const AnimationCharaChip& animCharaChip);
	~SkillSword();

	//!@brief �X�V����
	void	UpDate();
	//!@brief �`�揈��
	void	Render();

	//!@brief ���g�������鎞�Ԃ��v��
	//!@return 0�b�ɂȂ�����true
	bool	KillTime();

private:
};
