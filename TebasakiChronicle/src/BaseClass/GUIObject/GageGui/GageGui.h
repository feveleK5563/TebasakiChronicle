#pragma once
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/GUIObject/GUIObject.h"

//---------------------------------------------------------------------
//�T�v: �Q�[�W������GUI�I�u�W�F�N�g(�P�̂̂���)
//�����: �����
//---------------------------------------------------------------------
class GageGui 
{
private:
	//!@brief	�C�x���g���[�V����
	enum EventMotion
	{
		Ev_Non = 0,		//�Ȃ�
		Ev_Begin,		//�J�n
		Ev_Move,		//�ړ�
		Ev_Rotate,		//��]
		Ev_End,			//�I��
	};
public:
	//!@brief	�R���X�g���N�^
	explicit GageGui(GameObject& object);
	//!@brief	�f�X�g���N�^
	~GageGui();
	//!@brief	�X�V
	void		UpDate(GameObject& object);
	//!@brief	�`��
	void		Render();
	//!@brief	�C�x���g���J�n����
	//!@brief	�ĂԂƃC�x���g���J�n����
	void		EventStart();

private:
	//!@brief	��ԕύX����
	void	Think();
	//!@brief	��������
	void	Process();
	//!@brief	���[�V�����̍X�V
	//!@param[in]	eventMotion	���݂̃C�x���g���[�V����
	void	UpDateEventMotion(const EventMotion& eventMotion);
	//!@brief	�Q�[�W��ϓ������܂�
	void	Fluctuation(const K_Math::Vector3& targetPos);
	//!@brief	���Z�b�g
	void	Reset(GameObject& object);
private:
	//�R�s�[���֎~���܂�
	explicit GageGui(const GageGui& gageGui);
	GageGui& operator=(const GageGui& gageGui);

private:
	GUIObject		frame;			//�g
	GUIObject		fillAreaBox;	//��ɔz�u����Q�[�W

private:	//��
	int		minLife;
	int		maxLife;
	int		life;
private:
	int				moveCnt;		//�ړ����鎞��
	int				rotateCnt;		//��]���鎞��
	int				maxMoveCnt;		//�ő�ړ�����
	int				maxRotateCnt;	//�ő��]����
	K_Math::Vector3	maxShowLife;	//�ő�hp�Q�[�W�ʒu
	K_Math::Vector3	minShowLife;	//�ŏ�hp�Q�[�W�ʒu
	K_Math::Vector3 showLife;		//hp�Q�[�W�ʒu
	float			changeAmount;	//�ω���
	EventMotion		eventMotion;	//�C�x���g���[�V����
	bool			eventStartFlag;	//�C�x���g�X�^�[�g�t���O
};