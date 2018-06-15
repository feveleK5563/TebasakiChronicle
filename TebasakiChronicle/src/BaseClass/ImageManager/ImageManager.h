#pragma once
#include <math.h>
#include "AnimationCharaChip.h"

class ImageManager
{
private:
	const bool							isDelete;	//�o�^���ꂽcharaChip��delete���邩�ۂ�
	K_Graphics::SpriteObject*			spobj;		//�X�v���C�g�I�u�W�F�N�g
	std::vector<AnimationCharaChip*>	charaChip;	//�A�j���[�V�������x�A�T�C�Y�Ȃ�
	int									nowAnimNum;	//���݂̉摜�ԍ�
	float								animCnt;	//�A�j���[�V�����̃E�F�C�g

public:
	//�R���X�g���N�^
	//�L�����`�b�v��ImageManager���ō쐬���Ȃ��ꍇ�͑�������false���w��
	ImageManager(K_Graphics::Texture* tex, bool isde);

	//�f�X�g���N�^
	~ImageManager();

	//���݂̃L�����`�b�v���擾
	AnimationCharaChip* GetNowAnimationCharaChip();

	//----------------------------------------------
	//�L�����`�b�v�̍쐬
	bool CreateCharaChip(const K_Math::Box2D& src, int sheet, float spd, bool isroop);

	//----------------------------------------------
	//�L�����`�b�v��ύX
	//���R���X�g���N�^��isde��false�ɂ��Ă��Ȃ��Ǝ��s����
	bool ChangeCharaChip(const std::vector<AnimationCharaChip*>& acc);

	//----------------------------------------------
	//�A�j���[�V�����p�^�[���̕ύX
	void ChangeAnimationPattern(int motionNum, bool timeReset = true);

	//----------------------------------------------
	//�A�j���[�V����
	void Animation();

	//----------------------------------------------
	//�`��(3D)
	void ImageDraw3D(	const K_Math::Vector3&	posc, 
						const K_Math::Vector3&	angle,
						const K_Math::Vector3&	scale,
						int						direction);

	//----------------------------------------------
	//�`��(2D)
	void ImageDraw2D(	const K_Math::Vector3&	posc,
						const K_Math::Vector3&	angle,
						const K_Math::Vector3&	scale,
						int						direction);
};