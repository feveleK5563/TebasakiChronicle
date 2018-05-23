#include "EnemyLoader.h"

EnemyLoader::EnemyLoader(){}
EnemyLoader::~EnemyLoader(){}

//����1�F�p�����[�^�f�[�^�̓ǂݍ���
void EnemyLoader::LoadEnemyParamaterData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed)
{
	//�e�N�X�`���̃p�X
	std::string texPath;
	//�g�p����摜��
	std::string texName;
	//�ő�̗�
	int maxLife;
	//�t�^�_���[�W
	int hitDamage;
	//�ړ����x
	float moveSpeed;
	//�W�����v��
	float jumpPower;
	ifs >> texPath >> texName >> maxLife >> hitDamage >> moveSpeed >> jumpPower;

	ed->paramater = new EnemyType::ParameterData(texPath, texName, maxLife, hitDamage, moveSpeed, jumpPower);
}

//����2�F�R���W�����`��̐����Ɣz�u�f�[�^�̓ǂݍ���
void EnemyLoader::LoadEnemyCollisionData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed)
{
	//�x�[�X�R���W�����̌`��
	float shapeSize[3];
	ifs >> shapeSize[0] >> shapeSize[1] >> shapeSize[2];
	K_Physics::CollisionShape* bs = CC::CreateBoxShape(shapeSize[0], shapeSize[1], shapeSize[2]);
	//�����A���㔻��p�R���W�����̌`��
	K_Math::Vector3 cfp = { 0.f, -shapeSize[1], 0.f };
	K_Math::Vector3 chp = { 0.f, shapeSize[1], 0.f };
	K_Physics::CollisionShape* cs = CC::CreateBoxShape(shapeSize[0] - 1.f, 1.f, 1.f);
	//��_���A��J�����p�R���W�����̌`��
	K_Math::Vector3 rp;
	ifs >> rp.x >> rp.y >> rp.z;
	ifs >> shapeSize[0] >> shapeSize[1] >> shapeSize[2];
	K_Physics::CollisionShape* rs = CC::CreateBoxShape(shapeSize[0], shapeSize[1], shapeSize[2]);
	//���E�p�R���W�����̌`��
	K_Math::Vector3 vp;
	ifs >> vp.x >> vp.y >> vp.z;
	ifs >> shapeSize[0] >> shapeSize[1] >> shapeSize[2];
	K_Physics::CollisionShape* vs = CC::CreateBoxShape(shapeSize[0], shapeSize[1], shapeSize[2]);
	//�U������J�ڗp�R���W�����̌`��
	K_Math::Vector3 aap;
	ifs >> aap.x >> aap.y >> aap.z;
	ifs >> shapeSize[0] >> shapeSize[1] >> shapeSize[2];
	K_Physics::CollisionShape* aas = CC::CreateBoxShape(shapeSize[0], shapeSize[1], shapeSize[2]);

	ed->collision = new EnemyType::CollisionData(bs, rs, vs, aas, cs, rp, vp, aap, cfp, chp);
}

//����3�F����f�[�^�̓ǂݍ���
void EnemyLoader::LoadEnemyMoveData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed)
{
	int patternNum;		//����p�^�[���̑���
	ifs >> patternNum;
	for (int i = 0; i < patternNum; ++i)
	{
		//����̐ݒ�
		int totalMoveNum;	//����̐�
		ifs >> totalMoveNum;

		int* moveIdArr = new int[totalMoveNum] {};			//����ԍ�
		int* skillIdArr = new int[totalMoveNum] {};			//���̓��쒆�Ɏ󂯎���X�L���ԍ�(ID)
		int* durationTimeArr = new int[totalMoveNum] {};	//���̓���Ɉڍs����܂ł̎���
		//����ɍ��킹���A�j���[�V�����̐ݒ�
		K_Math::Box2D* srcArr = new K_Math::Box2D[totalMoveNum];			//�ꖇ�ڂ̃e�N�X�`���ǂݍ��݈ʒu
		K_Math::Vector2* basisPosArr = new K_Math::Vector2[totalMoveNum]{};	//�`�����W
		int* sheetArr = new int[totalMoveNum];								//1�A�j���[�V�����̃e�N�X�`������
		float* spdArr = new float[totalMoveNum];							//�A�j���[�V�����ҋ@����
		bool* irArr = new bool[totalMoveNum];								//���[�v���邩�ۂ�
		
		for (int i = 0; i < totalMoveNum; ++i)
		{
			ifs >>	*(moveIdArr + i) >> *(skillIdArr + i) >> *(durationTimeArr + i) >>
					(srcArr + i)->x >> (srcArr + i)->y >> (srcArr + i)->w >> (srcArr + i)->h >>
					(basisPosArr + i)->x >> (basisPosArr + i)->y >>
					*(sheetArr + i) >> *(spdArr + i) >> *(irArr + i);
		}
		
		//���̓���ւ̑J�ڏ���
		int* transitionIdArr = new int[patternNum];
		for (int i = 0; i < patternNum; ++i)
		{
			ifs >> *(transitionIdArr + i);
		}

		ed->movesetupdata.emplace_back(new EnemyMovePattern::MoveSetUpData(
			moveIdArr,
			skillIdArr,
			durationTimeArr,
			srcArr,
			basisPosArr,
			sheetArr,
			spdArr,
			irArr,
			transitionIdArr,
			patternNum,
			totalMoveNum));
	}
}

//�G���̓ǂݍ���
EnemyTypeManager::EnemyData* EnemyLoader::LoadEnemyData(const std::string& enemyDataPath)
{
	//�{���Ȃ炱���Ńt�@�C����ǂݍ���(���͉�)
	//Prototype�ɏo�Ă��錕�̎q

	EnemyTypeManager::EnemyData* ed = new EnemyTypeManager::EnemyData();

	std::ifstream ifs(enemyDataPath);
	if (!ifs)
	{
		return nullptr;
	}

	//�p�����[�^��ǂݍ���
	LoadEnemyParamaterData(ifs, ed);

	//�R���W�����̔z�u�f�[�^��ǂݍ���
	LoadEnemyCollisionData(ifs, ed);

	//����f�[�^��ǂݍ���
	LoadEnemyMoveData(ifs, ed);
	
	return ed;
}