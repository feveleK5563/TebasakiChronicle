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
	GageGui();
	//!@brief	�f�X�g���N�^
	~GageGui();

	//!@brief	�������Z�o����
	void		Raito(float maxValue,float nowValue,float raito);

	//!@brief	�ʒu�Ɋ�����K�p����
	void		ProcessPos();

	//!@brief	�X�V
	void		UpDate();
	//!@brief	�`��
	void		Render();

private:
	//!@brief	��ԕύX����
	void	Think();
	//!@brief	��������
	void	Process();
	//!@brief	���[�V�����̍X�V
	//!@param[in]	eventMotion	���݂̃C�x���g���[�V����
	void	UpDateEventMotion(const EventMotion& eventMotion);

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
	float			nowGagePos;		//�Q�[�W�̌��݈ʒu
	int				moveCnt;		//�ړ����鎞��
	int				rotateCnt;		//��]���鎞��
	int				beginCnt;		//���߂̃J�E���g
	int				maxMoveCnt;		//�ő�ړ�����
	int				maxRotateCnt;	//�ő��]����
	K_Math::Vector3	maxShowLife;	//�ő�hp�Q�[�W�ʒu
	K_Math::Vector3	minShowLife;	//�ŏ�hp�Q�[�W�ʒu
	float			showLife;		//hp�Q�[�W�ʒu
	int				timeCnt;
	EventMotion		eventMotion;	//�C�x���g���[�V����
};