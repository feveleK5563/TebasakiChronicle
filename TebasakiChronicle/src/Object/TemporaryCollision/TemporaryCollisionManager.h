#pragma once
#include "TemporaryCollision.h"

//�ꎞ�I�ɐ��������R���W�������Ǘ�����
class TemporaryCollisionManager
{
private:
	std::vector<TemporaryCollision*>	tempCollision;	//�ꎞ�I�ɐ��������R���W����

public:
	TemporaryCollisionManager();
	TemporaryCollisionManager(K_Physics::CollisionShape* cshape);
	~TemporaryCollisionManager();

	//�R���W�����𐶐�����
	void CreateTemporaryCollision(	K_Physics::CollisionShape*	shape,			//�R���W�����̌`��
									const CollisionMask&		mmask,			//�Ԃ���Ώ�
									const CollisionMask&		gmask,			//�T�u�R���W�������g���w��(�����̏ꍇ��Non)
									const K_Math::Vector3&		setpos,			//���W
									const K_Math::Vector3&		movevec,		//�ړ���
									const Status::Direction&	dir,			//�e�N�X�`���̌���
									const int					damage,			//�Ώۂɗ^����_���[�W��
									const int					deletetime,		//���g���폜����܂ł̎���
									const float					gravitySize,	//�d�͗�(0�Ŗ���)
									const bool					ishitground,	//�n�`�ɐڐG��������ł���t���O
									const bool					doground);		//�x�[�X�R���W������n�`�Ƃ��Ĉ����t���O

	//���������R���W�����Ƀe�N�X�`����ݒ肷��
	void SetAnimationCharaChip(	K_Graphics::Texture*	texture,
								const K_Math::Box2D&	src,
								int						sheet,
								float					spd,
								bool					isroop);

	//�R���W�����̍X�V���s��
	//�R���W����������ŗv�����������ꍇ���ł�����
	void Update();

	//�R���W�����̕`����s��
	void Render();
};