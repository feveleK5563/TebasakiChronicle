#pragma once
#include <math.h>
#include "CharacterBehavior.h"
#include "EnemyMoveTransition.h"
#include "../../../BaseClass/ImageManager/AnimationCharaChip.h"
#include "../../../Helper.h"

//�G����̃p�^�[����ێ�����
class EnemyMovePattern
{
public:
	struct MoveSetUpData	//�G�̓���p�^�[�������ɕK�v�ȃf�[�^
	{
		int*				moveIdArr;			//����ԍ�����ꂽ�z��̃A�h���X�l
		int*				behaviorIdArr;		//���쒆�Ɏ擾�\�ȐU�镑���ԍ�
		int*				durationTimeArr;	//����̌p�����Ԃ���ꂽ�z��̃A�h���X�l
		K_Math::Box2D*		srcArr;				//�A�j���[�V�����摜�̍ŏ��̈ʒu
		K_Math::Vector2*	basisPosArr;		//�`��̊���W(0, 0�Œ��S)
		int*				sheetArr;			//�A�j���[�V��������
		float*				spdArr;				//�A�j���[�V�������x
		bool*				isRoopArr;			//���[�v���邩�ۂ�
		int*				transitionIdArr;	//������p�^�[���ւ̑J�ڏ����̔ԍ�
		int					patternNum;			//����p�^�[���̑���
		int					totalMoveNum;		//����̑���

		MoveSetUpData(	int* miarr, int* siarr, int* dtarr, K_Math::Box2D* srcarr, K_Math::Vector2* basisposarr, int* shtarr,
						float* spdarr, bool* irarr, int* tiarr, int pnum, int tmnum):
			moveIdArr(miarr), behaviorIdArr(siarr), durationTimeArr(dtarr), srcArr(srcarr), basisPosArr(basisposarr), sheetArr(shtarr),
			spdArr(spdarr), isRoopArr(irarr), transitionIdArr(tiarr), patternNum(pnum), totalMoveNum(tmnum){}

		~MoveSetUpData()
		{
			Memory::SafeDeleteArr(moveIdArr);
			Memory::SafeDeleteArr(behaviorIdArr);
			Memory::SafeDeleteArr(durationTimeArr);
			Memory::SafeDeleteArr(srcArr);
			Memory::SafeDeleteArr(sheetArr);
			Memory::SafeDeleteArr(spdArr);
			Memory::SafeDeleteArr(isRoopArr);
			Memory::SafeDeleteArr(transitionIdArr);
		}
	};

private:
	struct MovePattern		//����̎�ށA���Ԃ��������
	{
		CharacterBehavior*	em;		//����������ōs��
		int behaviorId;		//���쒆�Ɏ擾�\�ȃX�L���ԍ�
		int moveTimeMax;	//����I���܂ł̎���

		MovePattern(int beId, int mtime) :
			em(nullptr),
			behaviorId(beId),
			moveTimeMax(mtime) {}
	};
	std::vector<MovePattern*> mp;
	std::vector<AnimationCharaChip*> animChip;
	std::vector<EnemyMoveTransition*> emt;

public:
	//�R���X�g���N�^
	EnemyMovePattern(const MoveSetUpData& msud);

	//�f�X�g���N�^
	~EnemyMovePattern();

	//������s���A���ݎ擾�\�ȃX�L���̔ԍ���Ԃ�
	int EMove(int& nowMoveOrder, int& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, bool& endMovePattern);

	//���쏇�����Z�b�g����
	void MoveReset(int& nowMoveOrder);

	//�����ݒ肷��
	void SetMoveAndTime(int moveNum, int skillId, int durationTime);

	//����p�^�[���J�ڏ�����ݒ肷��
	void SetTransition(int transitionNum);

	//�A�j���[�V�����̃L�����`�b�v��Ԃ�
	const std::vector<AnimationCharaChip*>& GetNowAnimChip();

	//�w��ԍ��̑J�ڏ��������s���A�N���A������true��Ԃ�
	bool IsTransition(int num, CollisionManager& colmanager, Status& status, const bool endMovePattern);
};