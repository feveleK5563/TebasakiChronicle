#pragma once
#include "../../BaseClass/Collision/CollisionManager.h"
#include "../../TimeCount.h"

//�ꎞ�I�ɐ��������R���W����
//(���Ԍo�߂ŏ�������A�P�Ƃœ������肷��)
class TemporaryCollision
{
private:
	K_Physics::CollisionShape*	cShape;			//�R���W�����̌`��
	CollisionManager			colmanager;		//�R���W�����f�[�^�̊Ǘ���
	GameObject		gameObject;			//�X�e�[�^�X�A�ړ���d�͂̓���A�摜�Ǘ��ASE�Aeasing���������
	TimeCount		timeCnt;			//���Ԍv��
	bool			isHitGround;		//���ꂪtrue���ƒn�`�ɐڐG��������ł���
	bool			isHitTarget;		//���ꂪtrue���ƑΏۂɐڐG��������ł���

public:
	//�R���X�g���N�^
	TemporaryCollision(	K_Physics::CollisionShape*	shape,				//�R���W�����̌`��
						const CollisionMask&		mmask,				//�T�u�R���W�����̂Ԃ���Ώ�
						const CollisionMask&		gmask,				//�T�u�R���W�������g���w��(�����̏ꍇ��Non)
						const K_Math::Vector3&		setpos,				//���W
						const K_Math::Vector3&		movevec,			//�ړ���
						const Status::Direction&	dir,				//�e�N�X�`���̌���
						const int					damage,				//�Ώۂɗ^����_���[�W��
						const int					deletetime,			//���g���폜����܂ł̎���
						const float					gravitySize,		//�d�͗�(0�Ŗ���)
						const bool					ishitground,		//�n�`�ɐڐG��������ł���t���O
						const bool					ishittarget);		//�ΏۂɐڐG��������ł���t���O

	//�f�X�g���N�^
	//�R���W�����̌`�����delete����
	~TemporaryCollision();

	//�摜�Ǘ��҂𐶐����A�����ɃL�����`�b�v��ݒ肷��
	void SetImageManagerAndCharaChip(	K_Graphics::Texture*	texture,
										const K_Math::Box2D&	src,
										int						sheet,
										float					spd,
										bool					isroop);

	//�X�V(���ł���ꍇ��true��Ԃ�)
	bool Update();

	//���Ńt���O�𗧂Ă�
	bool Extinction();

	//�`��
	void Render();
};