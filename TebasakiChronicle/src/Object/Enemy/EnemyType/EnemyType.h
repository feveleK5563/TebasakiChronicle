#pragma once
#include "EnemyMoveSet.h"
#include "../../../BaseClass/Collision/CollisionManager.h"

//EnemyMoveSet�Ƃ��̑��G�̐����ɕK�v�ƂȂ�G���
class EnemyType
{
public:
	struct ParameterData	//�G�̊e����
	{
		std::string		texturePath;	//�e�N�X�`���̃p�X
		std::string		textureName;	//�e�N�X�`����
		int				maxLife;		//�̗͏��
		int				hitDamage;		//�v���C���[�ɗ^����_���[�W
		float			moveSpeed;		//�ړ����x
		float			jumpPower;		//�W�����v��
		bool			isUseGravity;	//�d�͂𗘗p���邩�ۂ�

		ParameterData(std::string& tp, std::string& tn, int ml, int hd, float ms, float jp, bool isug):
			texturePath(tp), textureName(tn), maxLife(ml), hitDamage(hd), moveSpeed(ms), jumpPower(jp), isUseGravity(isug){}
	};
	struct CollisionData	//�R���W�����̏��
	{
		K_Physics::CollisionShape*	baseShape;			//�n�`�p�R���W�����̌`��
		K_Physics::CollisionShape*	receiveShape;		//��_���A�J�����K���p�R���W�����̌`��
		K_Physics::CollisionShape*	visibilityShape;	//���E�p�R���W�����̌`��
		K_Physics::CollisionShape*	attackAreaShape;	//�U������J�ڗp�R���W�����̌`��
		K_Physics::CollisionShape*	checkShape;			//�����A���㔻��p�R���W�����̌`��
		K_Math::Vector3		receivePos;		//��_���A�J�����K���p�R���W�����̈ʒu
		K_Math::Vector3		visibilityPos;	//���E�p�R���W�����̈ʒu
		K_Math::Vector3		attackAreaPos;	//�U������J�ڗp�R���W�����̈ʒu
		K_Math::Vector3		checkFootPos;	//��������R���W�����̈ʒu
		K_Math::Vector3		checkHeadPos;	//���㔻��R���W�����̈ʒu

		CollisionData(	K_Physics::CollisionShape* bs, K_Physics::CollisionShape* rs, K_Physics::CollisionShape* vs, K_Physics::CollisionShape* aas, K_Physics::CollisionShape* cs,
						K_Math::Vector3& rp, K_Math::Vector3& vp, K_Math::Vector3& aap, K_Math::Vector3& cfp, K_Math::Vector3& chp):
			baseShape(bs), receiveShape(rs), visibilityShape(vs), attackAreaShape(aas), checkShape(cs),
			receivePos(rp), visibilityPos(vp), attackAreaPos(aap), checkFootPos(cfp), checkHeadPos(chp){}
	};

private:
	EnemyMoveSet*			emSet;			//����܂Ƃ�
	ParameterData			paramData;		//�e����
	CollisionData			collisionData;	//�R���W�������
	K_Graphics::Texture*	textureData;	//�e�N�X�`�����

public:
	//�R���X�g���N�^
	EnemyType(const ParameterData& param, const CollisionData& col);
	//�f�X�g���N�^
	~EnemyType();

	//�G�l�~�[�̓���ݒ���擾
	EnemyMoveSet* GetEnemyMoveSet();
	//�摜�����擾
	const std::string& GetTextureName();
	//�̗͏�����擾
	const int GetMaxLife();
	//�v���C���[�ɗ^����_���[�W�ʂ��擾
	const int GetHitDamage();
	//1�t���[���̈ړ����x���擾
	const float GetMoveSpeed();
	//�W�����v�͂��擾
	const float GetJumpPower();
	//�d�͂𗘗p���邩�ۂ����擾
	const bool GetIsUseGravity();
	//�e�N�X�`�����擾
	K_Graphics::Texture* GetTexture();

	//�n�`�p�R���W�����f�[�^�̐����Ǝ擾
	K_Physics::CollisionData* CreateAndGetBaseCollisionData();
	//��_���p�R���W�����f�[�^�̐����Ǝ擾
	K_Physics::CollisionData* CreateAndGetRecieveDamageCollisionData();
	//��J�����K���p�R���W�����f�[�^�̐����Ǝ擾
	K_Physics::CollisionData* CreateAndGetRecieveCameraCollisionData();
	//���E�p�R���W�����f�[�^�̐����Ǝ擾
	K_Physics::CollisionData* CreateAndGetFieldofviewCollisionData();
	//�U������J�ڗp�R���W�����̐����Ǝ擾
	K_Physics::CollisionData* CreateAndGetAttackAreaCollisionData();
	//�����p�R���W�����̐����Ǝ擾
	K_Physics::CollisionData* CreateAndGetCheckFootCollisionData();
	//����p�R���W�����̐����Ǝ擾
	K_Physics::CollisionData* CreateAndGetCheckHeadCollisionData();
};
