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
int EnemyMoveSet::EMove(int& nowMoveOrder, int& nowPatternOrder, int& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	bool endMovePattern = false;	//����p�^�[�����ꏄ������(�Ō�܂ł�������)�ǂ������i�[
	int idNum = empattern[nowPatternOrder]->EMove(nowMoveOrder, timeCnt, colmanager, tempmanager, status, move, endMovePattern);

	//�p�^�[���̑J�ڏ����𖞂����Ă�����p�^�[���ύX
	for (int i = 0; i < (int)empattern.size(); ++i)
	{
		if (empattern[nowPatternOrder]->GetTransition(i, colmanager, status))
		{
			PatternTransition(nowMoveOrder, nowPatternOrder, timeCnt, i);
			break;
		}
	}

	return idNum;
}

//-----------------------------------------------------------------------------
//����p�^�[�����w��ԍ��ɑJ�ڂ�����
void EnemyMoveSet::PatternTransition(int& nowMoveOrder, int& nowPatternOrder, int& timeCnt, int patternNum)
{
	if (patternNum >= (int)empattern.size())
		return;

	empattern[nowPatternOrder]->MoveReset(nowMoveOrder);
	nowPatternOrder = patternNum;
	timeCnt = 0;
}