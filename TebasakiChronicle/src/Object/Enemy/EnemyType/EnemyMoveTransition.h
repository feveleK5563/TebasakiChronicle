#pragma once

//����p�^�[���J�ڂ̊��N���X
class EnemyMoveTransition
{
public:
	EnemyMoveTransition(){}
	virtual ~EnemyMoveTransition(){}
	virtual bool Transition() = 0;
};

//-----------------------------------------------
//�펞�g�p (��ȏ�ݒ肵���ꍇ����̕ۏ؂͂ł��Ȃ���)
class ETransition_Default : public EnemyMoveTransition
{
public:
	bool Transition();
};