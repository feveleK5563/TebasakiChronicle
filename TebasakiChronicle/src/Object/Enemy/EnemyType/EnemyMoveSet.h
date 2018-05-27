#pragma once
#include "EnemyMovePattern.h"

//EnemyMovePattern���܂Ƃ߂����
class EnemyMoveSet
{
private:
	std::vector<EnemyMovePattern*>		empattern;		//����p�^�[��


public:
	EnemyMoveSet();
	~EnemyMoveSet();

	//����p�^�[���W���̐���
	void CreateMotionPattern(EnemyMovePattern::MoveSetUpData& msud);

	//�w��p�^�[���ԍ��̃A�j���[�V������Ԃ�
	const std::vector<AnimationCharaChip*>& GetNowAnimChip(int nowPatternOrder);

	//���݂̓���p�^�[�������s���A���݃v���C���[���擾�\�ȃX�L���ԍ���Ԃ�
	int EMove(int& nowMoveOrder, int& nowPatternOrder, TimeCount& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);

	//����p�^�[�����w��ԍ��ɑJ�ڂ�����
	void PatternTransition(int& nowMoveOrder, int& nowPatternOrder, TimeCount& timeCnt, int patternNum);
};