#pragma once
#include <unordered_map>
#include "../BaseClass/ImageManager/ImageManager.h"
#include "../TimeCount.h"
#include "../CSTList.h"
#include "../Helper.h"

class EffectManager
{
public:
	enum EffectName
	{
		Effect1,
		Effect2,
	};
	
private:
	//�G�t�F�N�g�����ɕK�v�ȃf�[�^
	struct EffectData
	{
		AnimationCharaChip*		animChip;	//�A�j���[�V�����Ǘ�
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
	};
	std::vector<EffectObject*> effectObj;

	EffectManager();
	~EffectManager();

public:
	//�G�t�F�N�g�̃f�[�^���쐬���A�i�[����
	void CreateEffectData(EffectName effectName, K_Graphics::Texture* tex, AnimationCharaChip* anim, int endTime);
	//�w����W�Ɏw�肵���G�t�F�N�g�𐶐�����
	void CreateEffect(EffectName effectName, const K_Math::Vector3& setPos);

	//�G�t�F�N�g�̍X�V����
	void Run();

	//�G�t�F�N�g�̕`�揈��
	void Render();

	//�C���X�^���X�𓾂�
	static EffectManager* GetInstance();
};

namespace Effect
{

}