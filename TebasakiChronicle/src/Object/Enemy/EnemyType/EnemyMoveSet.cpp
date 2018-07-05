#include "EnemyMoveSet.h"

//�R���X�g���N�^
EnemyMoveSet::EnemyMoveSet() {}

//�f�X�g���N�^
EnemyMoveSet::~EnemyMoveSet()
{
	for (auto it : empattern)
		delete it;
}

//-----------------------------------------------------------------------------
//����p�^�[���W���̐���
void EnemyMoveSet::CreateMotionPattern(EnemyMovePattern::MoveSetUpData& msud)
{
	empattern.emplace_back(new EnemyMovePattern(msud));
}

//-----------------------------------------------------------------------------
//�w��p�^�[���ԍ��̃A�j���[�V������Ԃ�
const std::vector<AnimationCharaChip*>& EnemyMoveSet::GetNowAnimChip(int nowPatternOrder)
{
	return empattern[nowPatternOrder]->GetNowAnimChip();
}

//-----------------------------------------------------------------------------
//���݂̓���p�^�[�������s���A���݃v���C���[���擾�\�ȃX�L���ԍ���Ԃ�
int EnemyMoveSet::EMove(int& nowMoveOrder, int& nowPatternOrder, TimeCount& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, bool isTakeDamage)
{
	//����p�^�[�����ꏄ������(�Ō�܂ł�������)�ǂ������i�[
	bool endMovePattern = empattern[nowPatternOrder]->IsEndMovePattern(nowMoveOrder, timeCnt, tempmanager, status, move);

	//�p�^�[���̑J�ڏ����𖞂����Ă�����p�^�[���ύX
	for (int i = 0; i < (int)empattern.size(); ++i)
	{
		if (i != nowPatternOrder &&
			empattern[nowPatternOrder]->IsTransition(i, colmanager, status, endMovePattern, isTakeDamage))
		{
			empattern[nowPatternOrder]->EMoveEnd(nowMoveOrder, timeCnt, tempmanager, status, move);
			PatternTransition(nowMoveOrder, nowPatternOrder, timeCnt, i);
			break;
		}
	}

	//������s���A�擾�ł��铮��ԍ����󂯎��
	int behaviorId = empattern[nowPatternOrder]->EMove(nowMoveOrder, timeCnt, tempmanager, status, move);

	return behaviorId;
}

//-----------------------------------------------------------------------------
//����p�^�[�����w��ԍ��ɑJ�ڂ�����
void EnemyMoveSet::PatternTransition(int& nowMoveOrder, int& nowPatternOrder, TimeCount& timeCnt, int patternNum)
{
	if (patternNum >= (int)empattern.size())
		return;

	empattern[nowPatternOrder]->MoveReset(nowMoveOrder);
	nowPatternOrder = patternNum;
	timeCnt.ResetCntTime();
}