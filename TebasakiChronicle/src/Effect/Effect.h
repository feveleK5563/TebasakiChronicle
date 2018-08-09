#pragma once
#include <unordered_map>
#include "../BaseClass/ImageManager/ImageManager.h"
#include "../TimeCount.h"
#include "../CSTList.h"
#include "../Helper.h"

enum struct EffectName
{
	Effect1,
	Effect2,

	BossKnockEffect,
	BossBeamEffect1,
	BossBeamEffect2,
};

class EffectManager
{	
private:
	//�G�t�F�N�g�����ɕK�v�ȃf�[�^
	struct EffectData
	{
		AnimationCharaChip*		animChip;	//�A�j���[�V�����Ǘ�
		std::string				texName;	//�e�N�X�`����
		K_Graphics::Texture*	texture;	//�e�N�X�`��
		int						endTime;	//�I������
	};
	std::unordered_map<EffectName, EffectData*> effectData;

	//�G�t�F�N�g
	struct EffectObject
	{
		ImageManager*		imageManager;	//�摜�\���ƃA�j���[�V�������䂭��
		K_Math::Vector3		pos;			//�\�����W
		TimeCount			timeCnt;		//���ł܂ł̎��Ԍv��
		int					direction;		//�\���̌���
	};
	std::vector<EffectObject*> effectObj;

	EffectManager();
	~EffectManager();

public:
	//�G�t�F�N�g�̃f�[�^���i�[����
	void CreateEffectData(EffectName effectName, const std::string& texName, const std::string& texPath, AnimationCharaChip* anim, int endTime);
	//�w����W�Ɏw�肵���G�t�F�N�g�𐶐�����
	void CreateEffect(EffectName effectName, const K_Math::Vector3& setPos, int direction = 0);

	//�G�t�F�N�g�̍X�V����
	void Run();

	//�G�t�F�N�g�̕`�揈��
	void Render();

	//�S�ẴG�t�F�N�g�Ƃ��̃f�[�^���폜����
	void AllDeleteEffect();

	//�C���X�^���X�𓾂�
	static EffectManager* GetInstance();
};

namespace Effect
{
	//�G�t�F�N�g�̃f�[�^���i�[����
	void CreateEffectData(EffectName effectName, const std::string& texName, const std::string& texPath, AnimationCharaChip* anim);

	//�w����W�Ɏw�肵���G�t�F�N�g�𐶐�����
	void CreateEffect(EffectName effectName, const K_Math::Vector3& setPos, int direction = 0);

	//�G�t�F�N�g�̍X�V����
	void Run();

	//�G�t�F�N�g�̕`�揈��
	void Render();

	//�S�ẴG�t�F�N�g�Ƃ��̃f�[�^���폜����
	void AllDeleteEffect();
}