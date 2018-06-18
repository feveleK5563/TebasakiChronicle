#pragma once
#include "K_Math/MyMathFanctions.h"
#include "../BaseClass/Move.h"
#include "../BaseClass/easing.h"
#include "../BaseClass/Status/Status.h"
#include "../src/BaseClass/ImageManager/ImageManager.h"

//-------------------------------------------------------------
//�Q�[���I�u�W�F�N�g
//�T�v:�I�u�W�F�N�g�̕K�v�Œ���̋@�\��񋟂���
//�����:�����
//-------------------------------------------------------------
class GameObject
{
public:
	GameObject();
	~GameObject();

	//�ݒ菈��
	void	SetStatus();
	void	SetMove(const Move* move);
	void	SetImage(K_Graphics::Texture* tex, bool isde = true);
	void	SetSound();
	void	SetEasing();

	//�擾����
	Status&				GetStatus();
	Move&				GetMove();
	ImageManager&		GetImage();
	Easing&				GetEasing();

	//�X�e�[�^�X�̐ݒ�
	void	SetPos(const K_Math::Vector3& vec);
	void	SetAngle(const K_Math::Vector3& vec);
	void	SetScale(const K_Math::Vector3& vec);
	void	SetMoveVec(const K_Math::Vector3& vec);
	void	SetState(const Status::State& state);
	void	SetDirection(const Status::Direction& dir);
	void	SetAttackPoint(const int& atPoint);
	void	SetLife(const int& life);

	//�X�e�[�^�X�̎擾����
	Status::State&		GetState();
	K_Math::Vector3&	GetPos();
	K_Math::Vector3&	GetAngle();
	K_Math::Vector3&	GetScale();
	K_Math::Vector3&	GetMoveVec();
	Status::Direction&	GetDirection();
	int&				GetAttackPoint();
	int&				GetLife();

	//!@brief	����ł��邩�̃`�F�b�N
	//!@param[in]	���C�t���Ȃ� true ����Ȃ� false
	bool	IsDead();

private:
	Status			status;		//Status
	Move			move;		//�ړ�����
	ImageManager*	image;		//ImageManager
								//Sound
	Easing			easing;		//�C�[�W���O
};