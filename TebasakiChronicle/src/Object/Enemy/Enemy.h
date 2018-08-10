#pragma once
#include "EnemyType/EnemyType.h"
#include "../GameObject.h"

class Enemy
{
private:
	EnemyMoveSet*	ems;			//����(delete�֎~)
	TimeCount		timeCnt;		//���Ԍv��
	int				behaviorId;		//���݂̓G����ǂݎ��铮��ԍ�
	bool			isBoss;			//�������{�X���ۂ�

	bool	isUseGravity;			//�d�͂��g�p���邩�ۂ�

	int					nowMoveOrder;		//���݂̓��쏇��
	int					nowPatternOrder;	//���݂̓���p�^�[���ԍ�
	int					beforeMoveOrder;	//�O�̓��쏇��
	int					beforePatternOrder;	//�O�̓���p�^�[���ԍ�

	CollisionManager			collisionManager;		//�R���W�����̊Ǘ�
	TemporaryCollisionManager	tempCollisionManager;	//�ꎞ�I�ɐ�������R���W�����N���X
	GameObject					gameObject;				//�Q�[���I�u�W�F�N�g
	K_Math::Vector3				relativePos;			//���΍��W

	TimeCount					invalidTime;			//��_���[�W���̖��G���Ԍv��

public:
	//�X�L���ԍ��ƌ��݂̃e�N�X�`�����A�L�����`�b�v�ԍ����i�[
	//������J�����󂯗p�R���W�����̃^�O�Ɏw�肷��
	struct SkillAndCharaChip
	{
		K_Math::Vector3*		pos;
		const std::string*		textureName;
		int*					behaviorId;
		AnimationCharaChip*		nowCharaChip;
	};
	SkillAndCharaChip* skillAndChip;

	//�R���X�g���N�^
	Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum, bool isBoss = false);
	//�f�X�g���N�^
	~Enemy();

	//�G����ݒ�
	void SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum);

	//������Ԃɂ���
	void SetNonEnemy();

	//��Ԃ�S�ď�����Ԃɖ߂�
	void ResetAndActiveEnemy();

	//�X�V
	void Update();

	//���S���Ă���ۂ���Ԃ�
	bool IsDead();

	//��ʓ�����
	bool DecisionInScreen();

	//�R���W�����Ƃ̐ڐG����
	//�_���[�W���󂯂���true��Ԃ�
	bool RecieveCollisionOperation();

	//�^�O�ɏ����i�[
	//�̗͂�0�ɂȂ�����true��Ԃ�
	void SetTagData();

	//�A�j���[�V�����̍X�V
	void AnimationUpdate();
	
	//�`��
	void Render();


	//--------------------------------------------------------

	//���W��ݒ�
	void SetPos(const K_Math::Vector3& setPos);
	//���΍��W��ݒ�
	void SetRelativePos(const K_Math::Vector3& rePos);

	//���W���擾����
	const K_Math::Vector3& GetPos();
	//���W���I�t�Z�b�g
	void OffsetPos(const K_Math::Vector3& offPos);

	//�̗͂ƁA�_���[�W���󂯂����ۂ���ݒ肷��
	void SetLife(int life, bool isTakeDamage);
	//�̗͂��擾����
	const int& GetLife();
};
