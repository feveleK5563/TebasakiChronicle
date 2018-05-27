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
int EnemyMoveSet::EMove(int& nowMoveOrder, int& nowPatternOrder, TimeCount& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	bool endMovePattern = false;	//����p�^�[�����ꏄ������(�Ō�܂ł�������)�ǂ������i�[
	int behaviorId = empattern[nowPatternOrder]->EMove(nowMoveOrder, timeCnt, colmanager, tempmanager, status, move, endMovePattern);

	//�p�^�[���̑J�ڏ����𖞂����Ă�����p�^�[���ύX
	for (int i = 0; i < (int)empattern.size(); ++i)
	{
		if (i != nowPatternOrder &&
			empattern[nowPatternOrder]->IsTransition(i, colmanager, status, endMovePattern))
		{
			PatternTransition(nowMoveOrder, nowPatternOrder, timeCnt, i);
			break;
		}
	}

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