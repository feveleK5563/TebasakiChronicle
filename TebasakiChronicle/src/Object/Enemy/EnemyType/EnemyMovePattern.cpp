#include "EnemyMovePattern.h"

//�R���X�g���N�^
EnemyMovePattern::EnemyMovePattern(const MoveSetUpData& msud)
{
	for (int i = 0; i < msud.totalMoveNum; ++i)
	{
		mp.emplace_back(new MovePattern(*(msud.moveIdArr + i), *(msud.behaviorIdArr + i), *(msud.durationTimeArr + i)));
		animChip.emplace_back(new AnimationCharaChip(*(msud.srcArr + i), *(msud.sheetArr + i), *(msud.spdArr + i), *(msud.isRoopArr + i), *(msud.basisPosArr + i)));
	}
	for (int i = 0; i < msud.patternNum; ++i)
	{
		int hoge = *(msud.transitionIdArr + i);
		emt.emplace_back(new EnemyMoveTransition(hoge));
	}
}

//�f�X�g���N�^
EnemyMovePattern::~EnemyMovePattern()
{ 
	for (auto it : mp)
	{
		delete it;
	}

	for (auto it : animChip)
	{
		delete it;
	}

	for (auto it : emt)
	{
		delete it;
	}
}

//-----------------------------------------------------------------------------
//���삪�I���������ۂ���Ԃ�
bool EnemyMovePattern::IsEndMovePattern(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//timeCnt��moveTimeMax�𒴂�����A���̓���Ɉڍs����
	if (timeCnt.IsTimeEnd())
	{
		//�I�����̏���
		EMoveEnd(nowMoveOrder, timeCnt, tempmanager, status, move);

		++nowMoveOrder;
		if (nowMoveOrder >= (int)mp.size())
		{
			nowMoveOrder = 0;
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//������s���A���ݎ擾�\�ȃX�L���̔ԍ���Ԃ�
int EnemyMovePattern::EMove(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	if (timeCnt.GetNowCntTime() == 0)	//�ŏ��ɍs������
	{
		timeCnt.SetEndTime(mp[nowMoveOrder]->moveTimeMax);
		mp[nowMoveOrder]->em.Initialize(tempmanager, status, move, timeCnt);
	}

	// ����
	mp[nowMoveOrder]->em.Action(tempmanager, status, move, timeCnt);

	timeCnt.Run();
	return mp[nowMoveOrder]->behaviorId;
}

//-----------------------------------------------------------------------------
//�I�����̏������s��
void EnemyMovePattern::EMoveEnd(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	mp[nowMoveOrder]->em.Finalize(tempmanager, status, move);
	timeCnt.ResetCntTime();
}

//-----------------------------------------------------------------------------
//���쏇�����Z�b�g����
void EnemyMovePattern::MoveReset(int& nowMoveOrder)
{
	nowMoveOrder = 0;
}

//-----------------------------------------------------------------------------
//�A�j���[�V�����̃L�����`�b�v��Ԃ�
const std::vector<AnimationCharaChip*>&  EnemyMovePattern::GetNowAnimChip()
{
	return animChip;
}

//-----------------------------------------------------------------------------
//�w��ԍ��̑J�ڏ��������s���A�N���A������true��Ԃ�
bool EnemyMovePattern::IsTransition(int num, CollisionManager& colmanager, Status& status, const bool endMovePattern)
{
	return emt[num]->IsTransition(colmanager, status, endMovePattern);
}