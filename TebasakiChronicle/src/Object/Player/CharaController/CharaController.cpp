#include "CharaController.h"


//------------------------------------------------------------
//�T�v:�L�����R���g���[���[�̎���
//�����:�����
//------------------------------------------------------------


//-------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------
CharaController::CharaController()
	
{

}

//-------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------
CharaController::~CharaController()
{

}


//-------------------------------------------------
//�X�V����
//-------------------------------------------------

//�ړ��x�N�g�������炢�A���삷��
void	CharaController::UpDate(Move& move)
{
	//���X�e�B�b�N�̓|��Ă���[��
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0,K_Input::VpadStick::L);
	//�E������0�x�Ƃ�����]�x
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0,K_Input::VpadStick::L);

	//�������݂̂̈ړ�
	if (stickDepth != 0)
	{
		//�X�e�B�b�N�̊p�x�����ɓ|�����������i��
		move.GetMoveVec().x = cosf(stickAngle) * stickDepth * move.GetAddVec();
	}
	else
	//�X�����Ȃ��ꍇ�́A�����Ȃ�(���C�ł������~�܂�悤�ɂ���)
	{
		move.GetMoveVec().x *= Friction;
	}
}


//------------------------------------------------------
//�ړ��̓��̓X�e�B�b�N��������Ă��邩�̔���
bool	CharaController::IsLStickInput()
{
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0, K_Input::VpadStick::L);
	if (stickDepth == 0)
	{
		return false;
	}
	return true;
}