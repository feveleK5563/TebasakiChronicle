#include "GameObject.h"

//------------------------------------------------------------
//�T�v:�Q�[���I�u�W�F�N�g�̏���
//�����:�����
//------------------------------------------------------------

//---------------------------------------------
//�R���X�g���N�^
//---------------------------------------------
GameObject::GameObject()
	:image(nullptr)
{

}

//---------------------------------------------
//�f�X�g���N�^
//---------------------------------------------
GameObject::~GameObject()
{
	if (image != nullptr)
	{
		delete image;
		image = nullptr;
	}
}


//---------------------------------------------
//�ݒ菈��
//---------------------------------------------
//�X�e�[�^�X�̐ݒ�
void	GameObject::SetStatus()
{

}

//�ړ��̐ݒ�
void	GameObject::SetMove(const Move* move)
{
	this->move = *move;
}

//�摜�Ǘ��҂̐���
void	GameObject::SetImage(K_Graphics::Texture* tex, bool isde)
{
	if (image != nullptr)
		return;

	image = new ImageManager(tex, isde);
}

//�T�E���h�̐ݒ�
void	GameObject::SetSound()
{

}

//�C�[�W���O�̐ݒ�
void	GameObject::SetEasing()
{

}


//---------------------------------------------
//�擾����
//---------------------------------------------
//�X�e�[�^�X�̎擾
Status&	GameObject::GetStatus()
{
	return status;
}

//�ړ��̎擾
Move&	GameObject::GetMove()
{
	return move;
}

//�摜�̎擾
ImageManager&	GameObject::GetImage()
{
	return *image;
}

//�C�[�W���O�̎擾
Easing&	GameObject::GetEasing()
{
	return easing;
}


//-------------------------------------------------------------
//�ݒ菈��
//���e:object��[State]��ݒ肷�鏈��
//-------------------------------------------------------------

//[object�̈ʒu]�̐ݒ�
void	GameObject::SetPos(const K_Math::Vector3& vec)
{
	this->GetStatus().GetPos() = vec;
}

//[object�̌X��]�̐ݒ�
void	GameObject::SetAngle(const K_Math::Vector3& vec)
{
	this->GetStatus().GetAngle() = vec;
}

//[object�̊g��k��]�̐ݒ�
void	GameObject::SetScale(const K_Math::Vector3& vec)
{
	this->GetStatus().GetScale() = vec;
}

//[object�̈ړ���]�̐ݒ�
void	GameObject::SetMoveVec(const K_Math::Vector3& vec)
{
	this->GetMove().GetMoveVec() = vec;
}

//[object�̏��]�̐ݒ�
void	GameObject::SetState(const Status::State& state)
{
	this->GetStatus().GetState() = state;
}

//[object�̌���]�̐ݒ�
void	GameObject::SetDirection(const Status::Direction& dir)
{
	this->GetStatus().GetDirection() = dir;
}

//[object�̍U����]�̐ݒ�
void	GameObject::SetAttackPoint(const int& atPoint)
{
	this->GetStatus().GetAttackPoint() = atPoint;
}

//[object�̗̑�]�̐ݒ�
void	GameObject::SetLife(const int& life)
{
	this->GetStatus().GetLife() = life;
}


//--------------------------------------------------------------
//�X�e�[�^�X�̎擾����
//���e:[object�̃X�e�[�^�X]�̎擾
//--------------------------------------------------------------

//�X�e�[�^�X�̎擾
Status::State&		GameObject::GetState()
{
	return GetStatus().GetState();
}

//�ʒu�̎擾
K_Math::Vector3&	GameObject::GetPos() 
{
	return GetStatus().GetPos();
}

//�X���̎擾
K_Math::Vector3&	GameObject::GetAngle()
{
	return GetStatus().GetAngle();
}

//�g��k���̎擾
K_Math::Vector3&	GameObject::GetScale() 
{
	return GetStatus().GetScale();
}

//�ړ��ʂ̎擾
K_Math::Vector3&	GameObject::GetMoveVec()
{
	return GetMove().GetMoveVec();
}

//�����̎擾
Status::Direction&	GameObject::GetDirection()
{
	return GetStatus().GetDirection();
}

//�U���͂̎擾
int&				GameObject::GetAttackPoint() 
{
	return GetStatus().GetAttackPoint();
}

//�̗͂̎擾
int&				GameObject::GetLife()
{
	return GetStatus().GetLife();
}


//---------------------------------------------------------
//!@brief	����ł��邩�̃`�F�b�N
//!@param[in]	���C�t���Ȃ� true ����Ȃ� false
bool	GameObject::IsDead()
{
	if (GetLife() <= 0)
	{
		return true;
	}
	return false;
}