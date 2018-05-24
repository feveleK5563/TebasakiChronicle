#pragma once
#include <iostream>
#include <vector>
#include "SystemClass.h"
#include "MeshModel.h"
#include "..\..\CSTList.h"

//�摜�̕������(�L�����`�b�v)��ێ�������
class AnimationCharaChip
{
public:
	K_Math::Box2D	chip;			//�L�����`�b�v�̃T�C�Y
	int				chipSheetNum;	//�A�j���[�V��������
	float			animSpd;		//�A�j���[�V�������x
	bool			isAnimRoop;		//���[�v���邩�ۂ�(true�Ń��[�v����)
	K_Math::Vector2 basisRenderPos;	//�`�����W(�f�t�H���g��0, 0(���S))

	//�R���X�g���N�^
	AnimationCharaChip(const K_Math::Box2D& src, int sheet, float spd, bool ir, const K_Math::Vector2& renderPos = K_Math::Vector2(0, 0));

	//�f�X�g���N�^
	~AnimationCharaChip();
};